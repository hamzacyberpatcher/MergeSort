#include <iostream>
#include <SFML/Graphics.hpp>


sf::RenderWindow window(sf::VideoMode(1900, 480), "Merge Sort");
const int length = 190;
int arr[length];
bool isSorted = false;

void disp(void)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            exit(0);
        }
    }
    window.clear();
    for (int i = 0; i < length; i++)
    {
        sf::RectangleShape block(sf::Vector2f(10, arr[i]));
        block.setPosition(i * 10, 480 - arr[i]);
        window.draw(block);
    }
    window.display();
}

void merge(int low, int mid, int high) {
    int n1 = mid - low + 1; // Size of left subarray
    int n2 = high - mid;    // Size of right subarray

    // Dynamically allocate memory for temporary arrays
    int* left = new int[n1];
    int* right = new int[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        left[i] = arr[low + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = arr[mid + 1 + j];
    }

    // Merge the temporary arrays back into arr[low..high]
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements (if any)
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
        disp();
    }
    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
        disp();
    }
    delete[] left;
    delete[] right;
}

void mergeSort(int low, int high) {
    if (low < high) {
        // Find the middle point
        int mid = low + (high - low) / 2;

        // Sort first and second halves
        mergeSort(low, mid);
        mergeSort(mid + 1, high);

        // Merge the sorted halves
        merge(low, mid, high);
    }
    isSorted = true;
}

// Print the array
void printArray(int n) {
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    window.setFramerateLimit(60);
    srand(time(0));
    for (int i = 0; i < length; i++)
    {
        arr[i] = rand() % 390 + 10;
    }
    int n = length;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        if (!isSorted)
        {
            disp();
            mergeSort(0, n - 1);
        }
        disp();
        
    }

    return 0;
}
