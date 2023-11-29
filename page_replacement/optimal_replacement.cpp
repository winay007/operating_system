#include "iostream"

using namespace std;

void optimal_replacement(int *reference_string, int n, int frame_size)
{
    int frame[frame_size];
    for (int i = 0; i < frame_size; i++)
        frame[i] = -1;

    int page_faults = 0;
    for (int i = 0; i < n; i++)
    {
        bool page_found = false;
        for (int j = 0; j < frame_size; j++)
        {
            if (frame[j] == reference_string[i])
            {
                page_found = true;
                break;
            }
        }

        if (!page_found)
        {
            page_faults++;
            cout << "Page fault at address: " << reference_string[i] << endl;
            int furthest = -1, f_idx = 0;
            for (int i = 0; i < frame_size; i++)
            {
                int j = 0;
                for (j = i + 1; j < n; j++)
                {
                    if (reference_string[j] == frame[i])
                    {
                        if (j > furthest)
                        {
                            furthest = j;
                            f_idx = i;
                        }
                        break;
                    }
                }
                if (j == n)
                {
                    f_idx = i;
                    break;
                }
            }
            frame[f_idx] = reference_string[i];
        }
    }

    cout << "\nNumber of Page Faults : " << page_faults << endl;
}

int main()
{
    int n, frame_size;
    cout << "Enter the frame size: ";
    cin >> frame_size;
    cout << "Enter the size of reference string: ";
    cin >> n;

    int reference_string[n];
    cout << "Enter the contents of reference string: ";
    for (int i = 0; i < n; i++)
    {
        cout << "Enter reference " << i + 1 << ": ";
        cin >> reference_string[i];
    }
    optimal_replacement(reference_string, n, frame_size);
    return 0;
}