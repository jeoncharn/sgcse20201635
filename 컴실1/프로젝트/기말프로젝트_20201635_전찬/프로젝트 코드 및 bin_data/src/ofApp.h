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
    
    //start, water_loc, color_array의 배열을 동적 할당시키는 함수
    void arraymalloc();
    
    //color_array가 저장할 rgb값을 구하고, 저장해주는 함수
    void getavg();
    
    //물방울이 그림에 도착했을 때, 그림을 그리는 함수
    void drawfigure();
    
    //물방울이 떨어지는 것을 표현하는 함수
    void waterfall();
    
    //그림을 표현해줄 변수, image는 표현할 그림, main, unit, end는 화면에 보여질 그림이다.
    ofImage image, main, unit, end;
    
    // image의 세로와 가로
    int height, width;
    
    //3차원으로 이미지를 보기 위해 필요한 변수
    ofEasyCam view;
    
    //물방울이 바닥에 떨어지는지, 도형이 필드에 적용되었는지 확인하는 배열
    bool** start;
    
    //물방울의 위치를 표현해주는 변수
    int** water_loc;
    
    //pixel 정보를 담고 있는 array [i][j][3] / 0=r 1=g 2=b 이다.
    int*** color_array;
    
    //pixel 정보를 받을 객체
    ofPixels pixel_data;
    
    //실행을 컨트롤하는 변수, unit_flag = 1이면 unit의 편집, execute_flag = 1 이면 실행, end_flag = 1이면 종료를 의미한다.
    int unit_flag, execute_flag, end_flag;
    
    //20x20에서 unit 모양을 정하는 변수
    int select_block[20][20];
    
    //원하는 사진의 파일 이름을 입력시키는 변수
    const char* filename = "Warhol.jpg"; 
};
