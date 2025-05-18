#include <iostream>
#include <SFML/Graphics.hpp>

// --- TV Girl Color Palette ---
const sf::Color COLOR_DEFAULT = sf::Color(92, 26, 111);     // Very dark plum
const sf::Color COLOR_LEFT = sf::Color(116, 6, 69);    // Deep magenta
const sf::Color COLOR_RIGHT = sf::Color(15, 71, 159);   // Blue
const sf::Color COLOR_COMPARE = sf::Color(237, 39, 136);  // Bright pink
const sf::Color COLOR_SORTED = sf::Color(26, 44, 117);   // Dark navy
const sf::Color COLOR_BACKGROUND = sf::Color(15, 15, 30);    // Soft dark night tone

sf::RenderWindow window(sf::VideoMode(1900, 480), "Merge Sort Visualizer");
const int length = 190;
int arr[length];
bool isSorted = false;
sf::Color colors[length];

void disp()
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
    window.clear(COLOR_BACKGROUND);
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

    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[low + i];
        colors[low + i] = COLOR_LEFT;
    }
    for (int j = 0; j < n2; j++)
    {
        right[j] = arr[mid + 1 + j];
        colors[mid + 1 + j] = COLOR_RIGHT;
    }
    disp();

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2)
    {
        colors[k] = COLOR_COMPARE;
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

        disp();
        k++;
    }

    while (i < n1)
    {
        colors[k] = COLOR_COMPARE;
        arr[k] = left[i];
        i++;
        disp();
        k++;
    }

    while (j < n2)
    {
        colors[k] = COLOR_COMPARE;
        arr[k] = right[j];
        j++;
        disp();
        k++;
    }

    delete[] left;
    delete[] right;

    for (int m = low; m <= high; m++)
    {
        colors[m] = COLOR_SORTED;
    }
    disp();
}

void mergeSort(int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergeSort(low, mid);
        mergeSort(mid + 1, high);
        merge(low, mid, high);
    }
    isSorted = true;
}

int main()
{
    window.setFramerateLimit(175);
    srand(time(0));
    for (int i = 0; i < length; i++)
    {
        arr[i] = rand() % 390 + 10;
        colors[i] = COLOR_DEFAULT;
    }

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
            mergeSort(0, length - 1);
        }
        disp();
    }

    return 0;
}
