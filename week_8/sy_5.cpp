#include <iostream>
#include <vector>
using namespace std;


struct Pixel 
{
    int r, g, b;
    Pixel() : r(0), g(0), b(0) {}
    Pixel(int r_, int g_, int b_) : r(r_), g(g_), b(b_) {}
    bool operator!=(Pixel& other) 
    {
        return (r != other.r) || (g != other.g) || (b != other.b);
    }
};

int main() 
{

    int h, w;
    cin >> h >> w;

    vector<vector<Pixel>> prev_frame(h, vector<Pixel>(w));
    for (int i = 0; i < h; ++i)
     {
        for (int j = 0; j < w; ++j) 
        {
            int r, g, b;
            cin >> r >> g >> b;
            prev_frame[i][j] = Pixel(r, g, b);
        }
    }

    int change_cnt = 0;
    for (int i = 0; i < h; ++i) 
    {
        for (int j = 0; j < w; ++j) 
        {
            int r, g, b;
            cin >> r >> g >> b;
            Pixel curr(r, g, b);
            if (curr != prev_frame[i][j]) 
            {
                change_cnt++;
            }
        }
    }


    long long total_pixels = 1LL * h * w;
    long long original_bits = total_pixels * 24LL; 
    long long compressed_bits = 1LL * change_cnt * 48LL;
    long long ans = original_bits - compressed_bits;

    cout << ans << endl;

    return 0;
}