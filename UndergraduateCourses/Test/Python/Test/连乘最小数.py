def mix(mi):
        mixture = 1
        for i in range(6):
                mixture *= mi
                mi += 2
        return mixture


for j in range(1, 1000, 2):
        if mix(j) == 135135:
                print(j)
                break
