#ifndef _GRAPHICSDISPLAY_H_
#define _GRAPHICSDISPLAY_H_
#include <vector>
#include "observer.h"
#include "window.h"
class Cell;
class GraphicsDisplay: public Observer {
        const int windowSize = 500;     // Window constants
        const int gameSize = 400;
        const int border = (windowSize - gameSize) / 2;
        Xwindow *w;
        std::vector<std::vector<int>> gDisplay;
 //       int rows;       // Rows = n where the grid is n x n
        int size;       // Size of squares will be scaled according to number of rows
        public:
                GraphicsDisplay(Xwindow &w);
                ~GraphicsDisplay();
                void notify(Cell &c) override;
//                SubscriptionType subType() override;
                void clearG();         // Method for clearing display
};
#endif