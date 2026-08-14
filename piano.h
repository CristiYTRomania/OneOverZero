long double frequency(string c, long long n)
{
    long double p=pow(2,n-7),f=0/0.0;
         if(c=="A" ||c=="a")f=3520*p;
    else if(c=="G#"||c=="g#"||c=="Ab"||c=="ab")f=3322*p;
    else if(c=="G" ||c=="g")f=3136*p;
    else if(c=="F#"||c=="f#"||c=="Gb"||c=="gb")f=2960*p;
    else if(c=="F" ||c=="f" ||c=="E#"||c=="e#")f=2794*p;
    else if(c=="E" ||c=="e" ||c=="Fb"||c=="fb")f=2637*p;
    else if(c=="D#"||c=="d#"||c=="Eb"||c=="eb")f=2489*p;
    else if(c=="D" ||c=="d")f=2349*p;
    else if(c=="C#"||c=="c#"||c=="Db"||c=="db")f=2217*p;
    else if(c=="C" ||c=="c" ||c=="B#"||c=="b#")f=2093*p;
    else if(c=="B" ||c=="b" ||c=="Cb"||c=="cb")f=3951*p;
    else if(c=="A#"||c=="a#"||c=="Bb"||c=="bb")f=3729*p;
    return f;
}
void frequency()
{
    long long n;
    string c;
    cout<<"Nota din octava: ";
    cin>>c;
    cout<<"Octava: ";
    cin>>n;
    if(c[0]>='a' && c[0]<='z')
        c[0]-=32;
    cout<<c<<n<<" = "<<frequency(c,n)<<" Hz"<<endl;
}
