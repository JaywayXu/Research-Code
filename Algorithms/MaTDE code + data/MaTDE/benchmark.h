double min(double a, double b) {
    if (a < b)
        return a;
    else
        return b;
}

double Sphere(double y[], int task_id) {  // Sphere
    double z[MAX_NVARS], tmp[MAX_NVARS];
    double LB = -100, UB = 100;
    for (int i = 0; i < MAX_NVARS; i++) z[i] = LB + (UB - LB) * y[i];

    double s = 0;
    for (int i = 0; i < MAX_NVARS; i++) s += z[i] * z[i];

    fbest[task_id] = min(fbest[task_id], s);
    return s;
}

double Sphere2(double y[], int task_id) {  // Sphere
    double z[MAX_NVARS], tmp[MAX_NVARS];
    double LB = -100, UB = 100;
    for (int i = 0; i < MAX_NVARS; i++) z[i] = LB + (UB - LB) * y[i] - 80;

    double s = 0;
    for (int i = 0; i < MAX_NVARS; i++) s += z[i] * z[i];

    fbest[task_id] = min(fbest[task_id], s);
    return s;
}

double Sphere3(double y[], int task_id) {  // Sphere
    double z[MAX_NVARS], tmp[MAX_NVARS];
    double LB = -100, UB = 100;
    for (int i = 0; i < MAX_NVARS; i++) z[i] = LB + (UB - LB) * y[i] + 80;

    double s = 0;
    for (int i = 0; i < MAX_NVARS; i++) s += z[i] * z[i];

    fbest[task_id] = min(fbest[task_id], s);
    return s;
}

double Rosenbrock(double y[], int task_id) {  // Rosenbrock
    double s = 0;
    double LB = -MAX_NVARS, UB = MAX_NVARS;
    double z[MAX_NVARS];
    for (int i = 0; i < MAX_NVARS; i++) z[i] = LB + (UB - LB) * y[i] + 1;
    for (int i = 0; i < MAX_NVARS - 1; i++)
        s += 100 * (z[i] * z[i] - z[i + 1]) * (z[i] * z[i] - z[i + 1]) +
             (z[i] - 1) * (z[i] - 1);

    fbest[task_id] = min(fbest[task_id], s);
    return s;
}

double Ackley(double y[], int task_id) {  // Ackley
    double LB = -MAX_NVARS, UB = MAX_NVARS;
    double z[MAX_NVARS], tmp[MAX_NVARS];
    for (int i = 0; i < MAX_NVARS; i++) z[i] = LB + (UB - LB) * y[i] - 40;

    double s_a = 0, s_b = 0;
    for (int i = 0; i < MAX_NVARS; i++) {
        s_a += z[i] * z[i];
        s_b += cos(2.0 * PI * z[i]);
    }

    double s = 0.0;
    s = -20.0 * exp(-0.2 * sqrt(s_a / double(MAX_NVARS))) -
        exp(s_b / double(MAX_NVARS)) + 20.0 + exp(1.);

    fbest[task_id] = min(fbest[task_id], s);
    return s;
}

double Rastrgin(double y[], int task_id) {  // Rastrgin
    double z[MAX_NVARS], tmp[MAX_NVARS];
    double LB = -50, UB = 50;
    for (int i = 0; i < MAX_NVARS; i++) {
        if (i < 25)
            z[i] = LB + (UB - LB) * y[i] - 40;
        else
            z[i] = LB + (UB - LB) * y[i] + 40;
    }

    double s = 0.0;
    for (int i = 0; i < MAX_NVARS; i++)
        s += z[i] * z[i] - 10 * cos(2.0 * PI * z[i]) + 10;

    fbest[task_id] = min(fbest[task_id], s);
    return s;
}

double Griewank(double y[], int task_id) {  // Griewank
    double z[MAX_NVARS], tmp[MAX_NVARS];
    double LB = -100, UB = 100;
    for (int i = 0; i < MAX_NVARS; i++) {
        if (i < 25)
            z[i] = LB + (UB - LB) * y[i] + 80;
        else
            z[i] = LB + (UB - LB) * y[i] - 80;
    }

    double s_a = 0, s_b = 1.0;
    for (int i = 0; i < MAX_NVARS; i++) {
        s_a += z[i] * z[i];
        s_b *= cos(z[i] / sqrt(i + 1.0));
    }

    double s = 0;
    s = 1 + s_a / 4000.0 - s_b;

    fbest[task_id] = min(fbest[task_id], s);
    return s;
}

double power(double y, int k) {
    double s = 1;
    for (int i = 1; i <= k; i++) s *= y;
    return s;
}

double Weierstrass25D(double y[],
                      int task_id) {  // Weierstrass with 25 dimensions
    double z[25], tmp[25];
    double LB = -0.5, UB = 0.5;
    for (int i = 0; i < 25; i++) z[i] = LB + (UB - LB) * y[i] + 0.4;

    double s = 0;
    int k_max = 20;
    double a = 0.5, b = 3;
    for (int i = 0; i < 25; i++)
        for (int j = 0; j <= k_max; j++)
            s += power(a, j) * cos(2 * PI * power(b, j) * (z[i] + 0.5));
    for (int i = 0; i <= k_max; i++)
        s -= double(25) * power(a, i) * cos(2 * PI * power(b, i) * 0.5);

    fbest[task_id] = min(fbest[task_id], s);

    return s;
}

double Weierstrass50D(double y[],
                      int task_id) {  // Weierstrass with MAX_NVARS dimensions
    double z[MAX_NVARS], tmp[MAX_NVARS];
    double LB = -0.5, UB = 0.5;
    for (int i = 0; i < MAX_NVARS; i++) z[i] = LB + (UB - LB) * y[i] + 0.4;

    double s = 0;
    int k_max = 20;
    double a = 0.5, b = 3;
    for (int i = 0; i < MAX_NVARS; i++)
        for (int j = 0; j <= k_max; j++)
            s += power(a, j) * cos(2 * PI * power(b, j) * (z[i] + 0.5));
    for (int i = 0; i <= k_max; i++)
        s -= double(MAX_NVARS) * power(a, i) * cos(2 * PI * power(b, i) * 0.5);

    fbest[task_id] = min(fbest[task_id], s);
    return s;
}

double Schwefel(double y[], int task_id) {  // Schwefel
    double s = 418.9829 * double(MAX_NVARS);
    double LB = -500, UB = 500;
    double z[MAX_NVARS];
    for (int i = 0; i < MAX_NVARS; i++) z[i] = LB + (UB - LB) * y[i];
    for (int i = 0; i < MAX_NVARS; i++) s -= z[i] * sin(sqrt(fabs(z[i])));

    fbest[task_id] = min(fbest[task_id], s);

    return s;
}
