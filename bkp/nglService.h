//Здесь будут служебные функции

#pragma once
void showCursor(bool cursor);
void loadingAnim(int curPass);


void showCursor(bool cursor){
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&structCursorInfo);
	structCursorInfo.bVisible = cursor;
	SetConsoleCursorInfo( GetStdHandle(STD_OUTPUT_HANDLE), &structCursorInfo );
}



int tmp_1 = 1;
int tmp_2 = 200;

//Возмоно мы добавим анимацию позднее, пока эт озаглушка
void loadingAnim(int tmp_1){
    CN;
    tmp_1++;
    double procent = 100*double(tmp_1)/double(tmp_2);
    cout << "\r\t";
    setColor(LightCyan);
    for (int j = 0; j < int(procent)/2; j++)
        cout << char(-37);
    setColor(LightRed);
    for (int j = int(procent)/2; j < 100/2; j++)
			cout << ".";

    cout <<"   " << setprecision(4) << procent << "%";
    setColor(Black);
    cout << ".....";

}
