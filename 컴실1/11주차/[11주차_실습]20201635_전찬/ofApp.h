#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

    public:
        void setup();
        void update();
        void draw();

        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y );
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseEntered(int x, int y);
        void mouseExited(int x, int y);
        void windowResized(int w, int h);
        void dragEvent(ofDragInfo dragInfo);
        void gotMessage(ofMessage msg);
    
    /* WaterFall-related member variables Regions */
    
    // flag variables
    int draw_flag;
    int load_flag;
    int water_flag;
    
    // Line segment and dot related variables
    int num_of_line, num_of_dot;
    int selected_dot;
    int line_counter, dot_counter;
    float dot_diameter;
    
    //동적할당을 통해서 data 받아내기
    int** line_data;
    int** dot_data;
    
    //동적할당을 통해서 water line data 받아내는 변수
    float** waterline_data;
    //waterline의 개수
    int num_of_waterline;
    
    //완성된 waterline의 개수
    int waterline_counter;
    //현재 waterline의 끝점의 좌표
    float lastx2, lasty2;
    
    /* WaterFall-related member functions */
    
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    void initializeWaterLines(); // 2nd week portion.
        
};
