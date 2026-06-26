#include <stdio.h>

int c[] = {2,4,2,3,6,5,4,4,8,2,4,1,3,6,4,3,4,4,3};
int j[] = {2,3,3,4,2,3,3,4,2,4,5,3,3,2,4,5,3,3,1,2,1};
int f[] = {0,2,4,4,2,5,5,3,5,7,9,9,7,9,9,8,4,4,6,2,4,1,3,4,3,4,4,3};

int a[20], b[20];

int stroke(int u)
{
    int k = u - 0xAC00;
    return c[k/588] + j[(k%588)/28] + f[k%28];
}

int make(char s[], int arr[])
{
    int i, n = 0;
    for (i = 0; s[i] != 0; i += 3) {
        if ((s[i] & 0xF0) != 0xE0) continue;
        int u = ((s[i] & 0x0F) << 12) | ((s[i+1] & 0x3F) << 6) | (s[i+2] & 0x3F);
        if (u < 0xAC00 || u > 0xD7A3) continue;
        arr[n] = stroke(u);
        n++;
    }
    return n;
}

int love(int n1, int n2)
{
    int v[40], m = 0;
    for (int i = 0; i < n1 || i < n2; i++) {
        if (i < n1) v[m++] = a[i];
        if (i < n2) v[m++] = b[i];  
    }
    while (m > 2) {
        for (int i = 0; i < m - 1; i++)
            v[i] = (v[i] + v[i+1]) % 10;
        m--;
    }
    return v[0] * 10 + v[1];
}

void result(int p)
{
    int i;
    printf("궁합도: ");
    for (i = 0; i < p / 5; i++) printf("■");
    for (i = p / 5; i < 20; i++) printf("·");
    printf(" %d%%\n", p);

    if (p >= 90) {
        if (p == 99) printf("결혼까지 가세요~~~!!👩‍❤️‍👨👩‍❤️‍👨💐💐\n");
        else         printf("천생연분이에요! 💕\n");
    }
    else if (p >= 70) printf("잘 어울리는 사이!\n");
    else if (p >= 40) {
        if (p == 67) printf("six seven!!\n");
        else         printf("노력하면 가능성 있어요.\n");
    }
    else printf("좋은 친구네요.\n");
}

int main()
{
    char s1[100], s2[100];
    int n1, n2, p;

    while (1) {
        printf("내 이름: ");
        scanf("%s", s1);
        printf("상대 이름: ");
        scanf("%s", s2);

        n1 = make(s1, a);
        n2 = make(s2, b);
        if (n1 > 0 && n2 > 0) break;
        printf("한글 이름을 입력하세요.\n\n");
    }

    p = love(n1, n2);

    printf("\n%s님이 %s님을 %d%% 만큼 사랑합니다.\n", s1, s2, p);
    result(p);

    return 0;
}