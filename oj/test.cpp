#include <iostream>
#include <iomanip>
#include <algorithm>
int n, k;
#define eps 1e-9
using namespace std;
int main()
{   
    scanf("%d %d", &n, &k);
    FILE *vfile = fopen("values.txt", "r");
    FILE *pfile = fopen("prices.txt", "r");
    double *p, *v, *res;
    p = new double[n];
    v = new double[n];
    res = new double[n];
    for (int i = 0; i < n; i++)
    {
        fscanf(vfile, "%d ", &v[i]);
    }
    for (int i = 0; i < n; i++)
    {
        fscanf(pfile, "%d ", &p[i]);
    }
    double high = 1000000.0, low = 0.0, mid;
    for (int i = 0; i < 100; i++)
    {
        mid = (low + high) / 2;
        double sum = 0;
        for (int j = 0; j < n; j++)
        {
            res[j] = v[j] - mid * p[j];
        }
        sort(res, res + n, greater<double>());
        for (int j = 0; j < k; j++)
        {
            sum += res[j];
        }
        if (sum >= 0)
        {
            low = mid;
        }
        else
        {
            high = mid;
        }
        printf("low is %lf\n", low);
    }
    cout << setiosflags(ios::fixed) << setprecision(11) << low;
    return 0;
}