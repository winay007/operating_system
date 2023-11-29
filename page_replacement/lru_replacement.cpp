#include "iostream"

using namespace std;

void lru_replacement(int *reference_string, int n, int frame_size)
{
    int frame[frame_size], occurence[frame_size];
    for (int i = 0; i < frame_size; i++)
    {
        frame[i] = -1;
        occurence[i] = -1;
    }

    int page_faults = 0;
    for (int i = 0; i < n; i++)
    {
        int k = -1;
        for (int j = 0; j < frame_size; j++)
        {
            if (frame[j] == reference_string[i])
            {
                k = j;
                break;
            }
        }

        // update last occurence
        if (k != -1)
            occurence[k] = i;
        else
        {
            cout << "Page fault at address: " << reference_string[i] << endl;
            int least_recent = occurence[0], idx = 0;
            for (int j = 1; j < frame_size; j++)
            {
                if (occurence[j] < least_recent)
                {
                    least_recent = occurence[j];
                    idx = j;
                }
            }
            page_faults++;
            frame[idx] = reference_string[i];
            occurence[idx] = i;
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
    lru_replacement(reference_string, n,frame_size);
    return 0;
}