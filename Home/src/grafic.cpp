#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;
// g++ -o gf grafic.cpp -lbgi -lgdi32 -lcomdlg32 -luuid -loleaut32 -lole32

const long double eps = 1e-10;
const long double pi = acos(-1);
const long double e = 2.718281;
const long double inf = 1e12;

inline void setBackground()
{
    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeigth = GetSystemMetrics(SM_CYSCREEN);
    readimagefile("ImageBackground.jpg", 0, 0, screenWidth, screenHeigth);
}
int currentLanguage = 0; // 0 for Romanian, 1 for English, 2 for French
unordered_map<string, vector<string>> translationForLanguages;
typedef void (*functionD)(int, int, int, int);
class button
{
public:
    int x1, y1;
    int x2, y2;
    string txt;
    functionD dF;
    button(int xA, int yA, int xB, int yB, const string &text, void (*fct)(int, int, int, int))
    {
        txt = text;
        x1 = xA;
        x2 = xB;
        y1 = yA;
        y2 = yB;
        dF = fct;
    }
    void draw()
    {
        setcolor(WHITE);
        setfillstyle(SLASH_FILL, YELLOW);
        dF(x1, y1, x2, y2);
        if (!txt.empty())
        {
            settextstyle(3, HORIZ_DIR, 3);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy((x1 + x2) / 2, (y1 + y2) / 2, (char *)txt.c_str());
        }
    }
    bool isPressed()
    {
        POINT pos;
        GetCursorPos(&pos);
        if (x1 <= pos.x && pos.x <= x2 && y1 <= pos.y && pos.y <= y2 && GetAsyncKeyState(VK_LBUTTON))
            return true;
        return false;
    }
};
void mainMenu();
bool isValid(char c)
{
    if (isalnum(c) || c == ' ' || c == '*' || c == '+' || c == '-' || c == '^')
        return true;
    return false;
}
void updateText(int &x, int y, string &eq, char c)
{
    if (!isValid(c))
        ; // inform them somehow
    eq += c;
    string aux(1, c);
    outtextxy(x, y, (char *)aux.c_str());
    x += 15;
}
void backSpace(int &x, int y, string &eq)
{
    if (!eq.empty())
    {
        string aux(1, eq.back());
        eq.pop_back();
        x -= 15;
        outtextxy(x, y, (char *)aux.c_str());
        setfillstyle(SOLID_FILL, BLACK);
        bar(x - 10, y - 15, x + 15, y);
        setfillstyle(SLASH_FILL, YELLOW);
    }
}
void drawFunction(string s);
inline void functionInput()
{
    cleardevice();
    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeigth = GetSystemMetrics(SM_CYSCREEN);
    readimagefile("Blackboard.jpg", 0, 0, screenWidth, screenHeigth);
    string equation;
    char txtForFunction[105];
    strcpy(txtForFunction, translationForLanguages["Write your function here"][currentLanguage].c_str());
    outtextxy(screenWidth / 2 - 200, screenHeigth / 2 - 200, txtForFunction);

    int crtX = screenWidth / 2 - 300, crtY = screenHeigth / 2;
    setfillstyle(SOLID_FILL, BLACK);
    bar(screenWidth / 2 - 350, screenHeigth / 2 - 100, screenWidth / 2 + 300, screenHeigth / 2 + 100);
    setfillstyle(SLASH_FILL, YELLOW);
    while (1)
    {
        while (!kbhit())
            ;
        char c = getch();
        if (c != 8 && c != 13)
            updateText(crtX, crtY, equation, c);
        else if (c == 8)
            backSpace(crtX, crtY, equation);
        else
        {
            drawFunction(equation);
            break;
        };
    }
    mainMenu();
}
inline void initialize()
{
    DWORD screenWidth = GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeigth = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth, screenHeigth, "", -3, -3);
    translationForLanguages["Start"].push_back("Start");
    translationForLanguages["Start"].push_back("Start");
    translationForLanguages["Start"].push_back("Debut");

    translationForLanguages["Languages"].push_back("Limbi");
    translationForLanguages["Languages"].push_back("Languages");
    translationForLanguages["Languages"].push_back("Langues");

    translationForLanguages["Exit"].push_back("Iesire");
    translationForLanguages["Exit"].push_back("Exit");
    translationForLanguages["Exit"].push_back("Quitter");

    translationForLanguages["Write your function here"].push_back("Scrieti functia dumneavoastra aici");
    translationForLanguages["Write your function here"].push_back("Write your function here.");
    translationForLanguages["Write your function here"].push_back("Ecrivez votre fonction ici.");

    //setwritemode(XOR_PUT); doesn't work with text so, no use here
}
void changeLanguage(string language)
{
    if (language == "Romanian")
        currentLanguage = 0;
    else if (language == "English")
        currentLanguage = 1;
    else if (language == "French")
        currentLanguage = 2;
    else
        throw(__throw_bad_function_call);
}
void languagesMenu()
{
    cleardevice();

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeigth = GetSystemMetrics(SM_CYSCREEN);
    readimagefile("ImageBackground.jpg", 0, 0, screenWidth, screenHeigth);

    int xButtons = screenHeigth / 2;
    button romanianButton(300, xButtons, 400, xButtons + 100, "Romanian", bar);
    button englishButton(500, xButtons, 600, xButtons + 100, "English", bar);
    button frenchButton(700, xButtons, 800, xButtons + 100, "Francais", bar);
    button backButton(900, xButtons, 1000, xButtons + 100, "Exit", bar);
    romanianButton.draw();
    englishButton.draw();
    frenchButton.draw();
    backButton.draw();
    while (1)
    {
        if (romanianButton.isPressed())
            changeLanguage("Romanian");
        else if (englishButton.isPressed())
            changeLanguage("English");
        else if (frenchButton.isPressed())
            changeLanguage("French");
        else if (backButton.isPressed())
            break;
    }
    mainMenu();
}
void mainMenu()
{
    cleardevice();
    setBackground();
    button Start(200, 100, 400, 200, translationForLanguages["Start"][currentLanguage], bar);
    Start.draw();
    button Languages(200, 200, 400, 300, translationForLanguages["Languages"][currentLanguage], bar);
    Languages.draw();
    button Exit(200, 300, 400, 400, translationForLanguages["Exit"][currentLanguage], bar);
    Exit.draw();
    while (1)
    {
        if (Start.isPressed())
            functionInput();
        else if (Languages.isPressed())
            languagesMenu();
        else if (Exit.isPressed())
            exit(0);
    }
}
struct point
{
    int x, y;
};
struct myspace
{
    point centre;
    int dim, unit;
    long double pixel, maxx, maxy;

} space;
void drawPlus(int x1, int y1, int x2, int y2)
{
    int sz = max(y2 - y1, x2 - x1) / 5;
    bar(x1, (y2 + y1) / 2 - sz / 2, x2, (y2 + y1) / 2 + sz / 2);
    bar((x2 + x1) / 2 - sz / 2, y1, (x2 + x1) / 2 + sz / 2, y2);
}
void drawMinus(int x1, int y1, int x2, int y2)
{
    int sz = max(y2 - y1, x2 - x1) / 5;
    bar(x1, (y2 + y1) / 2 - sz / 2, x2, (y2 + y1) / 2 + sz / 2);
}
void draw_space(myspace space)
{
    setcolor(WHITE);
    rectangle(space.centre.x - space.dim, space.centre.y - space.dim, space.centre.x + space.dim, space.centre.y + space.dim);

    for (int i = 0; i <= space.dim; i += space.unit)
    {
        ///x=uri
        line(space.centre.x - i, space.centre.y - space.dim, space.centre.x - i, space.centre.y - space.dim + 5);
        line(space.centre.x + i, space.centre.y - space.dim, space.centre.x + i, space.centre.y - space.dim + 5);
        line(space.centre.x - i, space.centre.y + space.dim, space.centre.x - i, space.centre.y + space.dim - 5);
        line(space.centre.x + i, space.centre.y + space.dim, space.centre.x + i, space.centre.y + space.dim - 5);

        ///y-uri
        line(space.centre.x - space.dim, space.centre.y - i, space.centre.x - space.dim + 5, space.centre.y - i);
        line(space.centre.x - space.dim, space.centre.y + i, space.centre.x - space.dim + 5, space.centre.y + i);
        line(space.centre.x + space.dim, space.centre.y - i, space.centre.x + space.dim - 5, space.centre.y - i);
        line(space.centre.x + space.dim, space.centre.y + i, space.centre.x + space.dim - 5, space.centre.y + i);
    }

    setcolor(WHITE);
    line(space.centre.x - space.dim, space.centre.y, space.centre.x + space.dim, space.centre.y);
    line(space.centre.x, space.centre.y - space.dim, space.centre.x, space.centre.y + space.dim);
}

long double pixelvalue(int x, myspace space)
{
    return (x - space.centre.x) * space.pixel;
}

int sign(long double value)
{
    if (value < 0)
        return 1;
    return -1;
}

int normalizare(long double value)
{
    if (fabs(value) > space.maxy)
        return space.centre.y + sign(value) * space.dim;

    return space.centre.y + sign(value) * fabs(value) * space.unit;
}

long double number(string s, int &i)
{
    long double number = 0;
    while (i < (int)s.size() && '0' <= s[i] && s[i] <= '9')
    {
        number = number * 10 + s[i] - '0';
        i++;
    }
    if (i < (int)s.size() && s[i] == '.')
    {
        long double p = 0.1;
        i++;
        while (i < (int)s.size() && '0' <= s[i] && s[i] <= '9')
        {
            number = number + p * (s[i] - '0');
            i++;
        }
    }
    i--;
    return number;
}

int priority(char op)
{
    if (op < 0)
        return 4;

    if (op == '<' || op == '>' || op == '=')
        return 0;
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;

    return -1;
}

long double egal(long double a, long double b)
{
    return fabs(a - b) <= eps;
}

bool este_functie_cu_un_parametru(char c)
{
    return c == 's' || c == 'c' || c == 't' || c == 'a' || c == 'l';
}
bitset<10> compareResults; // results of compare operations
// this is useful in creating functions with {
int k;
bitset<10> crtCompareResults;
void process_op(stack<long double> &st, char op)
{
    long double r, l;
    r = st.top();
    st.pop();

    if (op < 0)
    {
        switch (-op)
        {
        case '+':
            st.push(r);
            break;
        case '-':
            st.push(-r);
            break;
        }
        return;
    }

    if (!este_functie_cu_un_parametru(op))
    {
        l = st.top();
        st.pop();
    }

    switch (op)
    {
    case '+':
        st.push(l + r);
        break;
    case '-':
        st.push(l - r);
        break;
    case '*':
        st.push(l * r);
        break;
    case '/':
        st.push(l / r);
        break;
    case '^':
        st.push(pow(l, r));
        break;

    case 's':
        st.push(sin(r));
        break;
    case 'c':
        st.push(cos(r));
        break;
    case 't':
        st.push(tan(r));
        break;
    case 'a':
        st.push(fabs(r));
        break;
    case 'l':
        if (!isnan(log(r)))
            st.push(log(r));
        else
            st.push(0);
        break; /// !!!!!!

    case '<':
        st.push((l < r));
        crtCompareResults[k++] = (l < r);
        break;
    case '>':
        st.push((l > r));
        crtCompareResults[k++] = (l > r);
        break;
    case '=':
        st.push(egal(l, r));
        crtCompareResults[k++] = egal(l, r);
        break;
    }
}

long double evaluate(string &s, long double x)
{
    k = 0;
    compareResults = crtCompareResults;
    stack<long double> st;
    stack<char> op;
    bool poate_este_unar = 1;

    for (int i = 0; i < (int)s.size(); i++)
    {
        /// doar spatiu
        if (s[i] == ' ')
            continue;

        /// variabila
        if (s[i] == 'x')
        {
            st.push(x);
            poate_este_unar = 0;
            continue;
        }
        if (s[i] == 'e')
        {
            st.push(e);
            poate_este_unar = 0;
            continue;
        }
        if (s[i] == 'p')
        {
            st.push(pi);
            poate_este_unar = 0;
            i++;
            continue;
        }

        if (este_functie_cu_un_parametru(s[i]))
        {
            op.push(s[i]);
            for (; s[i] != '('; i++)
                ;
            i--;
        }

        else if (s[i] == '(')
        {
            op.push('(');
            poate_este_unar = 1;
        }

        else if (s[i] == ')')
        {
            while (op.top() != '(')
            {
                process_op(st, op.top());
                op.pop();
            }

            op.pop();
            poate_este_unar = 0;

            if (!op.empty() && este_functie_cu_un_parametru(op.top()))
            {
                process_op(st, op.top());
                op.pop();
            }
        }

        else if ('0' <= s[i] && s[i] <= '9')
        {
            st.push(number(s, i));
            poate_este_unar = 0;
        }

        else
        {
            char op_cur = s[i];

            if (poate_este_unar && (op_cur == '+' || op_cur == '-'))
                op_cur = -op_cur;

            while (!op.empty() && ((s[i] != '^' && priority(op.top()) >= priority(op_cur)) || (priority(op.top()) > priority(s[i]))))
            {
                process_op(st, op.top());
                op.pop();
            }
            op.push(op_cur);
            poate_este_unar = 1;
        }
    }

    while (!op.empty())
    {
        process_op(st, op.top());
        op.pop();
    }
    return st.top();
}
void reEvaluateFunction(string s, myspace space)
{
    cleardevice();
    for (int punct = space.centre.x - space.dim; punct < space.centre.x + space.dim; punct++)
    {
        int y1 = normalizare(evaluate(s, pixelvalue(punct, space)));
        int y2 = normalizare(evaluate(s, pixelvalue(punct + 1, space)));
        setcolor(RED);
        if (compareResults == crtCompareResults && !isnan(y1) && !isnan(y2) && isfinite(y1) && isfinite(y2))
            line(punct, y1, punct + 1, y2);
    }
    draw_space(space);
}
void drawFunction(string s)
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeigth = GetSystemMetrics(SM_CYSCREEN);

    space.unit = 30;
    space.centre = {screenWidth / 2, screenHeigth / 2};
    space.dim = screenHeigth / 2 - 100;
    space.pixel = (long double)1 / space.unit;
    space.maxy = (long double)space.dim / space.unit;
    initwindow(screenWidth, screenHeigth, "", -3, -3);

    int spaceBorderX = space.centre.x + space.dim + 20;
    int spaceBorderY = space.centre.y + space.dim - 100;

    // draws plus and minus buttons
    button plusButton(spaceBorderX, spaceBorderY, spaceBorderX + 50, spaceBorderY + 50, "", drawPlus);
    button minusButton(spaceBorderX + 100, spaceBorderY, spaceBorderX + 150, spaceBorderY + 50, "", drawMinus);
    button ExitFunction(spaceBorderX + 200, spaceBorderY, spaceBorderX + 300, spaceBorderY + 100,
                        translationForLanguages["Exit"][currentLanguage], bar);

    setcolor(BLUE);
    reEvaluateFunction(s, space);
    plusButton.draw();
    minusButton.draw();
    ExitFunction.draw();
    while (1)
    {
        if (ExitFunction.isPressed())
            return;
        else if (plusButton.isPressed())
        {
            space.unit += 20;
            space.pixel = (long double)1 / space.unit;
            space.maxy = (long double)space.dim / space.unit;
            reEvaluateFunction(s, space);
            plusButton.draw();
            minusButton.draw();
            ExitFunction.draw();
        }
        else if (minusButton.isPressed() && space.unit > 20)
        {
            space.unit -= 20;
            space.pixel = (long double)1 / space.unit;
            space.maxy = (long double)space.dim / space.unit;
            reEvaluateFunction(s, space);
            plusButton.draw();
            minusButton.draw();
            ExitFunction.draw();
        }
    }
}
int main()
{
    initialize();
    mainMenu();

    return 0;
}
