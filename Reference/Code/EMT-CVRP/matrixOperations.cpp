#include "functions.h"
#include <armadillo>
#include <vector>
#include <stack>
using namespace arma;
using namespace std;

// M(n*m)

inline float get_alpha(float cx, float cy, float ax, float ay) {
    // P(cx, cy) -> Q(ax, ay)
    // L = sqr(alpha * cx - ax) + sqr(alpha * cy - ay)
    return (cx*ax+cy*ay) / (cx*cx+cy*cy);
}
inline float SQR(float a) {
    return a * a;
}
inline float calc_cost(mat &A, mat &M, mat &B, mat &D, float min_dist, float lambda, int col) {
    int n = A.n_rows, m = A.n_cols;
    mat t = zeros(A.n_rows, 1);
    // L2:
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < m; ++j) {
            t(i, 0) = t(i, 0) + A(i, j) * M(j, col);
        }
    }
    float res = 0;
    for(int i = 0; i < n; i++) {
        res += SQR(B(i, col) - t(i, 0));
    }
    res = sqrt(res);
    // L1:
    for(int i = 0; i < m; ++i) {
        float inner_pro = exp(D(i, 0) - min_dist) * D(i, 0);
        res += lambda * abs(inner_pro * M(i, col));
//        printf("inner_pro = %f\n", inner_pro);
    }
//    system("pause");
    return res;
}
float calc_point(float x1, float y1, float x2, float y2) {
    return sqrt(SQR(x1-x2) + SQR(y1-y2));
}
mat coordinate_descent(mat &A, mat &B, float lambda, float step) {
    int n = A.n_cols, m = B.n_cols;
    arma::mat M = arma::zeros(n, m);
    vector <float> steps;
    steps.push_back(-step);
    steps.push_back(step);
    float max_cost;
    int repair_count = 0;
    for(int col = 0; col < m; ++col) {
        arma::mat D = arma::zeros(n, 1);
        // get mat D
        float min_dist = MAX_FLOAT;
        int min_index = -BIG_DIS;
        for(int i = 0; i < n; ++i) {
            D(i, 0) = calc_point(A(0, i), A(1, i), B(0, col), B(1, col));
            if(min_dist > D(i, 0)) {
                min_dist = D(i, 0);
                min_index = i;
            }
        }
        max_cost = calc_cost(A, M, B, D, min_dist, lambda, col);
        int circle_size = 300;

        while(--circle_size > 0) {
            for(int i = 0; i < n; ++i) {
                for(int j = 0; j < steps.size(); ++j) {
                    float stp = steps[j];
                    M(i, col) = M(i, col) + stp;
                    float current_cost = calc_cost(A, M, B, D, min_dist, lambda, col);
                    if(M(i, col) > -EPS && current_cost < max_cost) {
                        max_cost = current_cost;
                    } else {
                        M(i, col) = M(i, col) - stp;
                    }
                }
            }
            if(col == 18) {
                print_mat_float(M);
            }
        }

//        repair_M
        int zero_count = 0;
        for(int i = 0; i < n; ++i) {
            if(abs(M(i, col) < EPS))
                zero_count++;
        }
        if(zero_count == n) {
            repair_count++;
            M(min_index, col) = get_alpha(A(0, min_index), A(1, min_index), B(0, col), B(1, col));
        }
    }
    if(repair_count > 0) {
        printf("repair count: %d\n", repair_count);
    }
//    mat temp = A * M;
//    printf("cost = %f\n", max_cost);
//    A.print("A");
//    temp.print("temp");
//    system("pause");
    return M;
}
mat standardization(mat &t) {
    mat variance = arma::zeros(t.n_rows, 1);
    float num = t.n_cols;
    for(int i = 0; i < t.n_rows; ++i)
    for(int j = 0; j < t.n_cols; ++j) {
        variance(i, 0) = variance(i, 0) + SQR(t(i, j));
    }
    for(int i = 0; i < t.n_rows; ++i) {
        variance(i, 0) = sqrt(variance(i, 0) / num);
        if(variance(i, 0) < EPS) {
            puts("standardization error variance near 0!");
            exit(-1);
        }
    }
    mat res = zeros(t.n_rows, t.n_cols);

//    variance.print("variance");
    for(int i = 0; i < t.n_rows; ++i) {
        for(int j = 0; j < t.n_cols; ++j) {
            res(i, j) = t(i, j) / variance(i, 0);
        }
    }
//    t.print("temp");
//    res.print("res");
//    system("pause");
    return res;
}
mat autoEncoder(mat A, mat B) {

//    least square L2 norm
//    mat C = (A.t() * A);
//    mat b = eye(C.n_rows, C.n_cols) * (1e-5);
//    mat inv_C = inv(C + b);
//    mat M = inv_C * A.t() * B;

    int n = A.n_cols, m = B.n_cols;
    A = standardization(A);
    B = standardization(B);
    float lambda = 5;
    float step = 0.02;
    mat M = coordinate_descent(A, B, lambda, step);
    return M;
}
// 传入的v包括了0点，此处把0点去掉
mat getVertexMatrix(int customer_size, vertex *v, vertex *c) {
    mat res(2, customer_size);
    for(int i = 0; i < customer_size; ++i) {
        // 中心化
        res(0, i) = v[i+1].x - c->x;
        res(1, i) = v[i+1].y - c->y;
    }
    return res;
}
// get distance matrix (D) by one solution
mat getDisMat(int customer_size, delimiter_individual &chromosome) {
    mat dist(customer_size, customer_size);
    dist.fill(BIG_DIS);
    for(int i = 0; i < customer_size; ++i)
        dist(i, i) = 0;
    vector <int> pos_of_zero;
    for(int i = 0; i < chromosome.count; ++i) {
        if(chromosome.sequence[i] == 0)
            pos_of_zero.push_back(i);
    }
    for(int i = 1; i < pos_of_zero.size(); ++i) {
        int ptl = pos_of_zero[i - 1];
        int ptr = pos_of_zero[i];
        for(int j = ptl + 1; j < ptr; ++j) {
            for(int k = j + 1; k < ptr; ++k) {
                int pos_l = chromosome.sequence[j] - 1;
                int pos_r = chromosome.sequence[k] - 1;
                dist(pos_l, pos_r) = dist(pos_r, pos_l) = (k - j) * EXPAND_RATE;
            }
        }
    }
    return dist;
}
// multi-dimension-scaling implement
mat getSquareMat(mat matrix) {
    mat sq = matrix;
    for(int i = 0; i < sq.n_rows; ++i) {
        for(int j = 0; j < sq.n_cols; ++j) {
            sq(i, j) = sq(i, j) * sq(i, j);
        }
    }
    return sq;
}
float getPosRowSum(mat d, int pos) {
    float res = 0;
    for(int i = 0; i < d.n_cols; ++i)
        res += d(pos, i);
    return res;
}
float getPosColSum(mat d, int pos) {
    float res = 0;
    for(int i = 0; i < d.n_rows; ++i)
        res += d(i, pos);
    return res;
}
float getSumOfMatrix(mat d) {
    float res = 0;
    for(int i = 0; i < d.n_rows; ++i) {
        for(int j = 0; j < d.n_cols; ++j) {
            res += d(i, j);
        }
    }
    return res;
}
mat getMultiDimensionScaling(mat D) {
    mat DSquare = getSquareMat(D);
    int n = DSquare.n_cols;
    mat H = eye<mat>(n, n) - ones<mat>(n, n) / n;
//    H.print("H:");
//    system("pause");
    mat K = H * ((-0.5) * DSquare) * H;
//    K.print("K:");
    K = (K + K.t()) / 2.0;
    vec val;
    mat eigvec;
    eig_sym(val, eigvec, K);


//    val.print("val");
//    system("pause");
    int feature_number = 0;
    for(int i = 0; i < n; ++i) {
        if(val[i] > EPS)
            feature_number++;
        if(val[i] <= EPS) val[i] = 0;
    }
    mat eigval(n, n);
//    printf("feature map: %d\n", feature_number);
    eigval.fill(0);
    for(int i = 0; i < eigval.n_cols; ++i)
        eigval(i, i) = val[i];

    mat res = eigvec * sqrt(eigval);
    mat ans(n, feature_number);
    ans.fill(0);
    int col = 0;
//    print_mat_float(res);
    for(int j = 0; j < res.n_cols; ++j) {
        bool conti = true;
        for(int i = 0; i < res.n_cols; ++i)
            if(abs(res(i, j)) > EPS)
                conti = false;
        if(conti) continue;
        for(int i = 0; i < res.n_rows; ++i) {
            ans(i, col) = res(i, j);
        }
        col++;
    }
//    print_mat_float(ans);
//    system("pause");
    return ans.t();
}
float calcDistance(mat &a, mat &b, int a_col, int b_col) {
    float dist = 0;
    for(int i = 0; i < a.n_rows; ++i) {
        dist += (a(i, a_col) - b(i, b_col))*(a(i, a_col) - b(i, b_col));
    }
    return sqrt(dist);
}

vector <int>pairwiseSorting(vector<int> &s, mat &D) {
    stack <int> stal, star;
    while(s.size() > 1) {
        int l, r;
        float max_dist = -1;
        for(int i = 0; i < s.size(); ++i) {
            for(int j = i + 1; j < s.size(); ++j) {
                if(max_dist < D(s[i], s[j])) {
                    max_dist = D(s[i], s[j]);
                    l = i, r = j;
                }
            }
        }
        if(stal.size() > 0 && D(s[l], stal.top()) + D(s[r], star.top())
            > D(s[r], stal.top()) + D(s[l], star.top())) {
            swap(l, r);
        }
        stal.push(s[l]);
        star.push(s[r]);
//        printf("L = %d  R = %d\n", s[l] + 1, s[r]);
        s.erase(s.begin() + max(l, r));
        s.erase(s.begin() + min(l, r));
//        for(int i = 0; i < s.size(); i++) {
//            printf("%d ", s[i] + 1);
//        }
//        puts("pair wise");
//        system("pause");
    }
    if(s.size() > 0)
        stal.push(s[0]);
    vector <int> ans;
    while(stal.size()) {
        ans.push_back(stal.top() + 1);
        stal.pop();
    }
    reverse(ans.begin(), ans.end());
    while(star.size()){
        ans.push_back(star.top() + 1);
        star.pop();
    }
    return ans;
}
undelimiter_individual kMeans(mat &data, int k, mat &original_dist) {
    int customer_size = data.n_cols;
    k = min(k, (int)data.n_cols);
    mat means;
    bool status = kmeans(means, data, k, random_spread, 10, false);
    if(status == false) {
        printf("kmeans faild!!!\n");
        exit(-1);
    }
    vector <int> sets[k];
    for(int i = 0; i < customer_size; i++) {
        int index_id = i;
        float min_dist = MAX_FLOAT;
        int optimize = -1;
        for(int j = 0; j < k; j++) {
            float dist = calcDistance(data, means, i, j);
            if(dist < min_dist) {
                min_dist = dist;
                optimize = j;
            }
        }
        sets[optimize].push_back(index_id);
    }

//    for(int i = 0; i < k; i++) {
//        printf("id: %d\n", i+1);
//        for(int j = 0; j < sets[i].size(); ++j) {
//            printf("%3d", sets[i][j] + 1);
//        }
//        puts("");
//    }
//    system("pause");

    undelimiter_individual ans;
    ans.fitness = MAX_FLOAT;
    ans.count = 0;

//    此处不用original_dist, 使用feature的mat
    mat feature_dist(customer_size, customer_size);
    for(int i = 0; i < customer_size; ++i) {
        for(int j = i + 1; j < customer_size; ++j) {
            feature_dist(i, j) = feature_dist(j, i) = calcDistance(data, data, i, j);
        }
    }
//    puts("feature mat");
//    print_mat_int(feature_dist);
    for(int cla = 0; cla < k; ++cla) {
        vector <int> temp = pairwiseSorting(sets[cla], feature_dist);

//        cout << "set size: " << sets[cla].size() << endl;
//        for(int i = 0; i < temp.size(); i++) {
//            cout << temp[i] << ' ';
//        }
//        cout << endl;

        for(int i = 0; i < temp.size(); ++i)
            ans.sequence[ans.count++] = temp[i];
    }
    return ans;
}
void print_MDS(mat &res) {
    puts("check");
    for(int i = 0; i < res.n_cols; ++i) {
        for(int j = 0; j < res.n_cols; ++j) {
            printf("%5.0f", calcDistance(res, res, i, j));
        }
        puts("");
    }
    system("pause");
}
float calc_error(mat &F, mat &D) {
    float res = 0;
    for(int i = 0; i < F.n_cols; ++i) {
        for(int j = 0; j < F.n_cols; ++j) {
            float temp = calcDistance(F, F, i, j);
            res += sqrt((temp - D(i, j)) * (temp - D(i, j)));
        }
    }
    return res;
}
void test_matrix() {
    float input_matrix[10][10] = {
        {0,1*EXPAND_RATE,2*EXPAND_RATE,BIG_DIS,1*EXPAND_RATE,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS},
        {1*EXPAND_RATE,0,3*EXPAND_RATE,BIG_DIS,3*EXPAND_RATE,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS},
        {2*EXPAND_RATE,3*EXPAND_RATE,0,BIG_DIS,2*EXPAND_RATE,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS},
        {BIG_DIS,BIG_DIS,BIG_DIS,0,BIG_DIS,2*EXPAND_RATE,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS},
        {1*EXPAND_RATE,3*EXPAND_RATE,2*EXPAND_RATE,BIG_DIS,0,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS},
        {BIG_DIS,BIG_DIS,BIG_DIS,2*EXPAND_RATE,BIG_DIS,0,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS},
        {BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,0,7*EXPAND_RATE,4*EXPAND_RATE,3*EXPAND_RATE},
        {BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,7*EXPAND_RATE,0,5*EXPAND_RATE,1*EXPAND_RATE},
        {BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,4*EXPAND_RATE,5*EXPAND_RATE,0,2*EXPAND_RATE},
        {BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,BIG_DIS,3*EXPAND_RATE,1*EXPAND_RATE,2*EXPAND_RATE,0},
    };
    mat D(10, 10);
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j) {
            D(i, j) = input_matrix[i][j];
        }
    }
    D.print("D:");
    mat res = getMultiDimensionScaling(D);
    res.print("res:");
    for(int i = 0; i < res.n_cols; ++i) {
        for(int j = 0; j < res.n_cols; ++j) {
            printf("%8.1f ", calcDistance(res, res, i, j));
        }
        puts("");
    }
    undelimiter_individual ans = kMeans(res, 3, D);
    for(int i = 0; i < ans.count; ++i) {
        cout << ans.sequence[i] << ' ';
    }
    cout << endl;
}

