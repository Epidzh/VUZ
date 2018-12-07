int a1 = 1, a2 = 5, n = 7;
    int first = 1, second = 2;

    int ans1 = first, ans2 = second;
    int i = 0;
    bool t = true;
    while (t)
    {
        i++;
        int num = second;
        second = first;
        first = (0 + num*a2) % n;
        second = (second + (num*a1)) % n;
        cout << i << ": " << first << " " << second << endl;
        if (first == ans1 && second == ans2)
            break;
        if (i > 10000)
            break;
    }