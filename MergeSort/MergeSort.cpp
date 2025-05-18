#include <iostream>
#include <SFML/Graphics.hpp>


sf::RenderWindow window(sf::VideoMode(1900, 480), "Merge Sort");
const int length = 190;
int arr[length];
bool isSorted = false;

sf::Color colors[length];  // Each bar will have its own color

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
        block.setFillColor(colors[i]);
        window.draw(block);
    }
    window.display();
}

void merge(int low, int mid, int high)
{
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* left = new int[n1];
    int* right = new int[n2];

    // Copy elements to temp arrays
    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[low + i];
        colors[low + i] = sf::Color::Yellow; // Left subarray = yellow
    }
    for (int j = 0; j < n2; j++)
    {
        right[j] = arr[mid + 1 + j];
        colors[mid + 1 + j] = sf::Color::Cyan; // Right subarray = cyan
    }
    disp();

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        colors[k] = sf::Color::Red; // Active merge comparison
        disp();

        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }

        colors[k] = sf::Color::Magenta; // Just written
        disp();
        k++;
    }

    while (i < n1)
    {
        colors[k] = sf::Color::Red;
        arr[k] = left[i];
        i++;
        colors[k] = sf::Color::Magenta;
        disp();
        k++;
    }

    while (j < n2)
    {
        colors[k] = sf::Color::Red;
        arr[k] = right[j];
        j++;
        colors[k] = sf::Color::Magenta;
        disp();
        k++;
    }

    delete[] left;
    delete[] right;

    // Mark merged section as green (sorted so far)
    for (int m = low; m <= high; m++)
    {
        colors[m] = sf::Color::Green;
    }
    disp();
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
    window.setFramerateLimit(175);
    srand(time(0));
    for (int i = 0; i < length; i++)
    {
        arr[i] = rand() % 390 + 10;
        colors[i] = sf::Color::White;
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
