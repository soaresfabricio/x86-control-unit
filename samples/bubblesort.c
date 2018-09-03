main()
{
    int a[10] = {1, 4, 2, 3, 10, 7, 5, 9, 8, 6};
    int n = 10;

    int temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }

    return a[0];
}