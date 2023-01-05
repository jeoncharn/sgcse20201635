#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //30프레임으로 설정
    ofSetFrameRate(60);
    
    main.load("main.png");
    unit.load("unit.png");
    end.load("end.png");
    image.load(filename);
    
    height = image.getHeight();
    width = image.getWidth();
    arraymalloc();
        
    ofLoadImage(pixel_data, filename);
    
    getavg();
    
    //unit의 기본값은 20x20의 꽉 찬 정사각형이다.
    for(int i=0; i<20; i++)
    {
        for(int j=0; j<20; j++)
        {
            select_block[i][j] = 1;
        }
    }
    
    unit_flag = 0;
    execute_flag = 0;
    end_flag = 0;

}

//--------------------------------------------------------------
void ofApp::update(){
    if(execute_flag)
    {
        //실행 중이라면, waterfall()을 통해서 물방울을 랜덤으로 시작하고, 시작한 경우에는 아래로 한 칸 내려준다.
        waterfall();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    if(execute_flag)
    {
        // 3차원으로 보기 위해
        view.begin();
        //ofDrawAxis(200);
        
        drawfigure();
        view.end();
    }
    
    //20x20 block을 어떻게 print할지 입력받는 부분이다
    else if(unit_flag)
    {
        ofSetColor(255, 255, 255);
        unit.draw(0, 0);
        
        //20x20배열을 선택된 부분은 파란색, 선택되지 않은 부분은 검은색으로 표시해준다.
        for(int i=0; i<20; i++)
        {
            for(int j=0; j<20; j++)
            {
                if(select_block[i][j])
                {
                    ofSetColor(0, 0, 255);
                    ofDrawRectangle(262 + i*25, 134 + j*25 + 10, 25, 25);
                }
                else
                {
                    ofSetColor(0, 0, 0);
                    ofDrawRectangle(262 + i*25, 134 + j*25 + 10, 25, 25);
                }
            }
        }
    }
    
    else if(end_flag)
    {
        // 프로그램이 종료된 경우
        ofSetColor(255, 255, 255);
        end.draw(0, 0);
    }
    
    else
    {
        //main 화면인 경우
        ofSetColor(255, 255, 255);
        main.draw(0, 0);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    
    //q 키가 한 번만 동작할 수 있도록, q가 입력되면 동적할당 해제와 함께, 프로그램 종료 화면을 보여준다.
    if(key=='q'&&!end_flag)
    {
        unit_flag = 0;
        execute_flag = 0;
        end_flag = 1;
        
        // 동적할당 해제
        for(int i=0; i<width/20; i++)
        {
            delete(start[i]);
            delete(water_loc[i]);
            for(int j=0; j<height/20; j++)
            {
                delete(color_array[i][j]);
            }
            delete(color_array[i]);
        }
        delete(start);
        delete(water_loc);
        delete(color_array);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    // unit을 편집하는 경우 좌클릭으로 유닛을 선택하고, 우클릭으로 유닛을 해제한다.
    if(unit_flag)
    {
        if(x< 262 + 500&&y< 134 + 500 && x>262 && y>134)
        {
            if(button==0)
            {
                select_block[(x-262)/25][(y-134)/25] = 1;
            }
            else if(button==2)
            {
                select_block[(x-262)/25][(y-134)/25] = 0;
            }
        }
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(button==0)
    {
        // main 화면인 경우에, unit 변경과 실행 부분을 클릭하면 적절하게 실행될 수 있도록
        if(!unit_flag&&!execute_flag&&!end_flag)
        {
            if(x>317&&y>468&&x<317+391&&y<468+71)
            {
                unit_flag = 1;
            }
            else if(x>317&&y>584&&x<317+391&&y<584+71)
            {
                execute_flag = 1;
            }
        }
        
        //unit 화면에서 왼쪽 위의 뒤로가기를 누르면 main 화면으로 돌아간다.
        if(unit_flag)
        {
            if(x>44&&y>44&&x<44+60&&y<71+44)
            {
                unit_flag = 0;
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::arraymalloc()
{
    // 동적 할당이 필요한 3가지 변수(color_array, start, water_loc)을 동적 할당 시켜주며, 각 원소의 값을 모두 0으로 초기화시킨다.
    color_array = new int** [width/20];
    start = new bool* [width/20];
    water_loc = new int* [width/20];
    for(int i=0; i<width/20; i++)
    {
        start[i] = new bool [height/20];
        color_array[i] = new int* [height/20];
        water_loc[i] = new int [height/20];
        for(int j=0; j<height/20; j++)
        {
            start[i][j] = 0;
            water_loc[i][j] = 0;
    
            color_array[i][j] = new int [3];
            color_array[i][j][0] = 0;
            color_array[i][j][1] = 0;
            color_array[i][j][2] = 0;
        }
    }
    
    return;
}

void ofApp::getavg()
{
    for(int i=0; i<width/20; i++)
    {
        for(int j=0; j<height/20; j++)
        {
            // 모서리 4 점을 기준으로 color rgb value를 얻어내며, 평균을 color_array에 저장한다.
            ofColor color = pixel_data.getColor(i*20, j*20);
            color_array[i][j][0] += ((float)color.r)/4;
            color_array[i][j][1] += ((float)color.g)/4;
            color_array[i][j][2] += ((float)color.b)/4;
            
            color = pixel_data.getColor(i*20+19, j*20);
            color_array[i][j][0] += ((float)color.r)/4;
            color_array[i][j][1] += ((float)color.g)/4;
            color_array[i][j][2] += ((float)color.b)/4;
            
            color = pixel_data.getColor(i*20, j*20+19);
            color_array[i][j][0] += ((float)color.r)/4;
            color_array[i][j][1] += ((float)color.g)/4;
            color_array[i][j][2] += ((float)color.b)/4;
            
            color = pixel_data.getColor(i*20+19, j*20+19);
            color_array[i][j][0] += ((float)color.r)/4;
            color_array[i][j][1] += ((float)color.g)/4;
            color_array[i][j][2] += ((float)color.b)/4;
            
        }
    }
    
    return;
}

void ofApp::drawfigure()
{
    // 3차원 기준 (0, 0, 0) 가운데가 되도록 그림을 그려준다.
    
    //ofSetColor(0, 0, 0);
    //ofDrawRectangle(-width/2, -height/2, (width/20)*20, (height/20)*20);
    
    for(int i=0; i<width/20; i++)
    {
        for(int j=0; j<height/20; j++)
        {
            // 물방울이 바닥에 도착한 경우, 그림을 표현해주는 부분이다.
            if(start[i][j]==1 && water_loc[i][j]==0)
            {
                for(int a=0; a<20; a++)
                {
                    for(int b=0; b<20; b++)
                    {
                        if(select_block[a][b]==1)
                        {
                            ofSetColor(color_array[i][j][0], color_array[i][j][1], color_array[i][j][2]);
                            ofDrawRectangle(i*20 + a - width/2, (height/20)*20-height/2 - (j*20 + b), 1, 1);
                        }
                    }
                }
            }
            
            //물방울을 표현해주는 부분이다. water_loc이 0이 아니면 물방울을 적절한 위치에, 그 위치의 평균색으로 표현해준다.
            else if(start[i][j]==1)
            {
                ofSetColor(color_array[i][j][0], color_array[i][j][1], color_array[i][j][2]);
                ofDrawSphere(i*20 + 10 - width/2, (height/20)*20-height/2 - (j*20 + 10), water_loc[i][j], 5);
            }
        }
    }
}

void ofApp::waterfall()
{
    for(int i=0; i<width/20; i++)
    {
        for(int j=0; j<height/20; j++)
        {
            //물방울이 아직 떨어지지 않았다면, 1/300 확률로 물방울을 drop ,,
            if(start[i][j]==0 && (rand()%300==0))
            {
                start[i][j] = 1;
                water_loc[i][j] = 500;
            }
            
            //물방울이 떨어지며, 도착하지 않은 경우, 물방울을 한 칸 아래로 이동시킨다
            else if(water_loc[i][j]>0)
            {
                water_loc[i][j] = water_loc[i][j] - 2;
            }
            
            //start = 1이고 water_loc = 0 인 경우에는 물방울이 이미 떨어진 형태이다.
        }
    }
    
    return;
}

