void StartProgram(int ok=0)
{
    if(ok != 0)
        system("clear") && system("cls");
    if(ok==0 || ok==1)
    {
        cout<<"Type 'help' for instructions! \n";
        cout<<"Introduceti 'ajutor' pentru instructiuni! \n";
    }
    else
        cout<<"MATH GAME \n";
}
int level = 1;
void math_game(bool language)
{
    cout<<endl;
    StartProgram(2);
    srand(time(0));
    int n,x,y,total,correct,lives;
    string s;
    while(level>=1 and level<=6)
    {
        correct=0;
        if(level>=1 and level<=5)
            total=5;
        else if(level==6)
            total=6;
        cout<<endl;
        if(language==1)
            cout<<"Nivelul ";
        else
            cout<<"Level ";
        cout<<level<<endl;
        cout<<"Help options: \n"<<"'play' for playing; \n"<<"'quit' (or 'exit') for quitting the game.";
        cout<<endl<<endl<<"> ";
        cin>>s;
        s=NotCaseSensitive(s);
        if(s=="quit" or s=="exit")
        {
            cout<<endl;
            StartProgram(1);
            break;
        }
        else if(s=="play")
        {
            lives = 3;
            while(correct<total && lives > 0)
            {
                if(level>=0 and level<=5)
                {
                    x=rand()%(level*2+1);
                    y=rand()%(level*2+1);
                }
                else if(level==6)
                {
                    x=rand()%21;
                    y=rand()%21;
                }
                cout<<x<<" + "<<y<<" = ";
                cin>>n;
                if(x+y==n)
                {
                    correct++;
                    cout<<"Correct answer! (";
                    if(lives<3)
                        lives++;
                }
                else
                {
                    cout<<"Wrong answer! (";
                    lives--;
                }
                cout<<correct<<"/"<<total<<")\n";
                cout<<"Lives: "<<lives<<endl;
            }
            if(correct==total)
            {
                if(level<6)
                {
                    level++;
                    cout<<"You reached level "<<level<<"! \n";
                }
                else
                    cout<<"Level 7 coming soon! \n";
            }
            else
                cout<<"Good luck next time! \n";
        }
        else if(language==1)
            cout<<"Comanda necunoscuta \n";
        else
            cout<<"Unknown command \n";
    }
}
