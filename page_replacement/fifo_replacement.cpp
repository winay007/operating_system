#include "iostream"

using namespace std;

void fifo_replacement(int *reference_string, int n, int frame_size)
{
    int frame[frame_size];
    for (int i = 0; i < frame_size; i++)
        frame[i] = -1;

    int out = 0, page_faults = 0;
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
            frame[out] = reference_string[i];
            out = (out + 1) % frame_size;
            cout << "Page fault at address: " << reference_string[i] << endl;
            page_faults++;
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
    fifo_replacement(reference_string, n, frame_size);
    return 0;
}