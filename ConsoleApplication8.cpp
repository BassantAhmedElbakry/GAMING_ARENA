#include<dos.h>
#include<windows.h>
#include<iostream>
#include< chrono >
#include<string>
#include <cstdlib>
#include <ctime>
#include<conio.h>

using namespace std;
using namespace std::chrono;


void board();//initialize function to draw the board

int check_progress();//initialize function to check game progress

int roll_dice();//initialize function to roll dice

//the we declare some variables

int roll; //holds the rolled value for the player
int computer_roll; //holds the rolled value for computer

char input; //variable to hold the users input, any number to roll dice and 0 to quit game, although entering a not a number value ends  the game as well...

int progress; //holds the value for the progress

int player = 0;

int computer = 0;

int squares[101]; // for the 100 squares, computers right counts from 0

struct stack {
    int s[5];
    int top;
} st;

struct stack1 {
    int s1[5];
    int top1;
} st1;

void push(int item, int top)
{
    st.s[top] = item;
}
void push1(int item1, int top1)
{
    st1.s1[top1] = item1;
}
void delay(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

int pop(int top)
{
    int item;
    item = st.s[top];
    return (item);
}
int pop1(int top1)
{
    int item1;
    item1 = st1.s1[top1];
    return (item1);
}


struct node
{
    char key;
    struct node* left, * right;
};

struct nodel
{
    char data;
    struct nodel* next;

}*p = NULL, * startt = NULL;

struct node1
{
    char data1;
    struct node1* next1;

}*p1 = NULL, * start1 = NULL;
void SetColor(int ForgC)
{
    WORD wColor;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi)) //O(1)
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
void ClearConsoleToColors(int ForgC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
    //Get the handle to the current output buffer...
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    //This is used to reset the carat/cursor to the top left.
    COORD coord = { 0, 0 };
    //A return value... indicating how many chars were written
      //   not used but we need to capture this since it will be
        //   written anyway (passing NULL causes an access violation).
    DWORD count;

    //This is a structure containing all of the console info
// it is used here to find the size of the console.
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    //Here we will set the current color
    SetConsoleTextAttribute(hStdOut, wColor);
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //This fills the buffer with a given character (in this case 32=space).
        FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);

        FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
        //This will set our cursor position for the next print statement.
        SetConsoleCursorPosition(hStdOut, coord);
    }
    return;
}

void inserte(char x)
{
    struct nodel* ptr = (struct nodel*)malloc(sizeof(struct nodel));
    ptr->data = x;
    if (p == NULL)
    {
        p = ptr;
        p->next = NULL;

    }
    else {
        startt = p;// Start is used to keep the track of first pointer, after ending of this part we will point p to start
        while (p->next != NULL) //O(n)
        {

            p = p->next;

        }
        p->next = ptr;
        ptr->next = NULL;
        p = startt;
    }
}
void inserte1(char x)
{
    struct node1* ptr1 = (struct node1*)malloc(sizeof(struct node1));

    ptr1->data1 = x;
    if (p1 == NULL)
    {
        p1 = ptr1;
        p1->next1 = NULL;

    }
    else {
        start1 = p1;// Start is used to keep the track of first pointer, after ending of this part we will point p to start
        while (p1->next1 != NULL) //O(n)
        {

            p1 = p1->next1;

        }
        p1->next1 = ptr1;
        ptr1->next1 = NULL;
        p1 = start1;
    }
}
void display()
{

    startt = p;// Start is used to keep the track of first pointer, after ending of this part we will point p to start
    while (p != NULL) //O(n)
    {
        printf("%c ", p->data);
        p = p->next;
    }
    p = startt;
    printf("\n");

}
void display1()
{

    start1 = p1;// Start is used to keep the track of first pointer, after ending of this part we will point p to start
    while (p1 != NULL) //O(n)
    {
        printf("%c ", p1->data1);
        p1 = p1->next1;
    }
    p1 = start1;
    printf("\n");

}

void inorder(struct node* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%c \n", root->key);
        inorder(root->right);
    }
}
int search(struct node* root, char key) {


    while (root->key != key) //O(n) in worst case and O(log n) in average case
    {

        if (root != NULL) {
            //go to left tree
            if (root->key > key) {
                root = root->left;
            }//else go to right tree
            else {
                root = root->right;
            }

            //not found
            if (root == NULL) {
                return -1;
            }
        }
    }
    return 1;
}
// A utility function to create a new BST node
struct node* newNode(char item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
struct node* insert(struct node* node, char key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

int main()

{
    auto start = high_resolution_clock::now();
    int zh1;
    int zh2;
    int zh3;
    int zh4;
    int zh5;
    int zh6;
    int zh7;
    int zh8;
    int zh9;
    int zh10;
    int zh11;
    int zh12;
    int c;


    ClearConsoleToColors(0, 15);
    do {
        system("cls"); SetColor(4);
        string q = "\t\t\tWELCOME TO GAMING ARENA";
        zh1 = q.size();
        for (int i = 0; i < zh1; i++) //O(n)
        {
            cout << q[i];
            delay(120);

        }
        cout << endl; SetColor(1);
        cout << "\t\t\t1. Ladder and Snake\n\t\t\t2. Bollywood\n\t\t\t3. Line Racing\n\t\t\t4. Country Quiz\n\t\t\t5.Time execution of code\n\t\t\t6. Exit\n";
        char c;
        cout << "\t\t\tEnter your choice: ";
        //cin >> c;
        c = _getch();

        switch (c)
        {
        case '1': {
            system("cls");
            string q = "WELCOME TO LADDER AND SNAKE";
            zh12 = q.size();
            for (int i = 0; i < zh12; i++) //O(n)
            {
                cout << q[i];
                delay(120);
            }
            cout << endl << endl;
            char z;
            cout << "Welcome to the ladder and snake game In this game you can play with the computer.To win this game you need to reach the top point first by moving according to the rolled dice number.If you reach the bottom of a ladder you will be able to climb up but beware of reaching the head of a snake or it will drag you down. " << endl << endl;
            cout << "Press any letter to continue : ";
            //cin >> z;
            z = _getch();
            system("cls");
            srand(time(NULL)); //we need random numbers remeber?

            string alert = ""; //to alert you for your triumphs and misfortunes
            string computer_alert = ""; // to alert you for computer's triumphs and misfortunes

            cout << "Enter any number to roll dice, press 0 to quit\n\n";
            cout << "SNAKES\tLADDERS\n99-5\t4-36\n93-25\t8-28\n77-9\t20-41\n52-6\t35-67\n30-2\t45-66\n\n";
            cout << "200 represents the player and 300 represents the computer\n\n";

            for (int i = 1; i <= 100; i++) //O(n)
        // this loop just makes it possible for us to give our squares values
            {
                squares[i] = i;
            }

            do // every game is in some sort of loop
            {
                cout << "Enter: ";
                cin >> input;

                roll = roll_dice();//player rolls dice

                if ((roll + player) > 100)
                {
                    player = player; //player has rolled a number that exceeds the end point player remains where they are
                }
                else
                {
                    squares[player] = player;//overwrite the current position
                    player = player + roll;//move player to a new position
                }

                computer_roll = roll_dice();//computer rolls dice

                if ((computer_roll + computer) > 100)
                {
                    computer = computer; //computer has rolled a number that exceeds the end point, computer remains where it is
                }
                else
                {
                    squares[computer] = computer;//overwrite the current position
                    computer = computer + computer_roll;//move computer to a new position
                }

                switch (player) // it is snakes and ladders, numbers represent the snakes and ladders
                {
                case 99:
                    player = 5;
                    alert = "OOPS... You ran into a SNAKE!";
                    break;

                case 93:
                    player = 25;
                    alert = "OOPS... You ran into a SNAKE!";
                    break;

                case 77:
                    player = 9;
                    alert = "OOPS... You ran into a SNAKE!";
                    break;

                case 52:
                    player = 6;
                    alert = "OOPS... You ran into a SNAKE!";
                    break;

                case 30:
                    player = 2;
                    alert = "OOPS... You ran into a SNAKE!";
                    break;

                case 45:
                    player = 66;
                    alert = "YAY! you climbed a ladder!!!";
                    break;

                case 35:
                    player = 67;
                    alert = "YAY! you climbed a ladder!!!";
                    break;

                case 20:
                    player = 41;
                    alert = "YAY! you climbed a ladder!!!";
                    break;
                case 8:
                    player = 28;
                    alert = "YAY! you climbed a ladder!!!";
                    break;

                case 4:
                    player = 36;
                    alert = "YAY! you climbed a ladder!!!";
                    break;

                default:
                    alert = "";

                }

                switch (computer)
                {
                case 99:
                    computer = 5;
                    computer_alert = "OOPS... Computer ran into a SNAKE!";
                    break;

                case 93:
                    computer = 25;
                    computer_alert = "OOPS... Computer ran into a SNAKE!";
                    break;

                case 77:
                    computer = 9;
                    computer_alert = "OOPS... Computer ran into a SNAKE!";
                    break;

                case 52:
                    computer = 6;
                    computer_alert = "OOPS... Computer ran into a SNAKE!";
                    break;

                case 30:
                    computer = 2;
                    computer_alert = "OOPS... Computer ran into a SNAKE!";
                    break;

                case 45:
                    computer = 66;
                    computer_alert = "HAHA! computer climbed a ladder!!!";
                    break;

                case 35:
                    computer = 67;
                    computer_alert = "HAHA! computer climbed a ladder!!!";
                    break;

                case 20:
                    computer = 41;
                    computer_alert = "HAHA! computer climbed a ladder!!!";
                    break;

                case 8:
                    computer = 28;
                    computer_alert = "HAHA! computer climbed a ladder!!!";
                    break;

                case 4:
                    computer = 36;
                    computer_alert = "HAHA! computer climbed a ladder!!!";
                    break;

                default:
                    computer_alert = "";
                }

                squares[player] = 200; //player's position shall be represented by the integer 200
                squares[computer] = 300; //computer's position shall be represented by the inteer 300

                if (input != '0')
                {
                    cout << "You rolled " << roll << " Computer rolled " << computer_roll << endl;
                    cout << "Your Position: " << player << " Computer's Position: " << computer << endl;
                    cout << alert << endl;
                    cout << computer_alert << endl;

                    board();
                    cout << "SNAKES\tLADDERS\n99-5\t4-36\n93-25\t8-28\n77-9\t20-41\n52-6\t35-67\n30-2\t45-66\n\n"; //so the player knows which is a snake and that which is ladder
                }

                progress = check_progress();

            } while (progress == 0 && input != '0'); //O(n)

            if (squares[100] == 200)
            {
                cout << "You Win!" << endl;
            }
            else if (squares[100] == 300)
            {
                cout << "||Game Over Computer Wins!" << endl;
            }
            else
            {
                cout << "You Quit!";
            }

            cin.get();
            cin.ignore();

            break;
        }
        case '2': {

            system("cls");
            string q = "WELCOME TO BOLLYWOOD";
            zh2 = q.size();
            for (int i = 0; i < zh2; i++) //O(n)
            {
                cout << q[i];
                delay(120);

            }
            cout << endl << endl;
            char z;
            cout << "This is the conventional movie guessing game in which one is asked to correctly guess each letter one at a time. If the letter occurs in movie name, the character is displayed, or else the chance is cut and in this way if you are void of remaining chances, game is over." << endl << endl;
            cout << "Press any letter to continue : ";
            //cin >> z;
            z = _getch();
            system("cls");
            char a[][100] =
            {
                "JOHNNY GADDAR",
                "DRISHYAM",
                "VEER ZAARA",
                "RAMAIYA VASTAVAIYA",
                "AE DIL HAI MUSHKIL",
                "SADDA ADDA",
                "RAABTA",
                "DUM LAGA KE HAISHA",
                "CHAIN KHULI KI MAIN KHULI",
                "PINK",
                "36 CHINA TOWN",
                "FUN2SHH",
                "3 IDIOTS",
                "CHAK DE INDIA",
                "MUNNA BHAI MBBS",
                "KUCHH KUCHH HOTA HAI",
                "ANDAAZ APNA APNA",
                "TAARE ZAMEEN PAR",
                "KHOSHLA KA GHOSLA",
                "PAAN SINGH TOMAR",
                "MR X",
                "DIL BECHARA",
                "D DAY",
                "COCKTAIL",
                "JAJANTARAM MAMANTARAM",
                "LAGAAN",
                "MS DHONI",
                "KOI MIL GYA",
                "ZINDAGI NA MILEGI DOBARA",
                "ROCK ON"
            };
            srand(time(NULL));
            int x = rand() % 30;
            string s = a[x];


            struct node* root = NULL;
            root = insert(root, s[0]);
            zh3 = s.size();
            for (int i = 1; i < zh3; i++) //O(n)
            {
                if (s[i] != ' ')
                    insert(root, s[i]);
            }

            string s3 = "bollywood";
            string s2;
            string s4;
            int count = 9;
            zh4 = s.size();
            for (int i = 0; i < zh4; i++) //O(n)
            {
                if (s[i] == ' ')
                    s2.push_back(' ');
                else s2.push_back('*');


            }
            zh5 = s.size();
            for (int i = 0; i < zh5; i++) //O(n)
            {
                if (s[i] == 'A')
                    s2[i] = 'A';
                if (s[i] == 'E')
                    s2[i] = 'E';
                if (s[i] == 'I')
                    s2[i] = 'I';
                if (s[i] == 'O')
                    s2[i] = 'O';
                if (s[i] == 'U')
                    s2[i] = 'U';


            }
            cout << "You can press 0 to quit\n";
            cout << "Your movie is" << endl;
            cout << s2 << endl;
            while (1)
            {
                fflush(stdin);
                char ch;
                cout << "Enter a character to find : ";
                cin >> ch;
                ch = toupper(ch);
                if (ch == '0')
                {
                    cout << "YOU QUIT\n";
                    break;
                }
                if (search(root, ch) == -1)
                {
                    for (int j = 0; j < 9; j++) //O(n)
                    {
                        if (s3[j] != '*')
                        {
                            s3[j] = '*';
                            break;
                        }

                    }
                    s4.push_back(ch);
                    SetColor(12);
                    cout << "Sorry the character was not present in the string" << endl;
                    SetColor(1);
                    cout << "Characters left : " << s3 << endl;
                    cout << "Wrong Entries : " << s4 << endl;
                    cout << "Film Status: " << s2 << endl;

                    count--;
                    cout << endl;
                }
                else
                {
                    zh6 = s.size();
                    for (int i = 0; i < zh6; i++) //O(n)
                    {
                        if (s[i] == ch)
                        {
                            s2[i] = ch;
                        }
                    }
                    SetColor(10);
                    cout << "Character found!!" << endl;
                    SetColor(1);
                    cout << "Characters left : " << s3 << endl;
                    cout << "Wrong Entries : " << s4 << endl;
                    cout << "Film Status: " << s2 << endl;

                    cout << endl;

                }
                if (count == 0)
                {
                    SetColor(12);
                    cout << "Sorry! You ran out of chances" << endl;
                    SetColor(1);
                    cout << "Movie was: " << s << endl;
                    break;
                }
                if (find(s2.begin(), s2.end(), '*') == s2.end())
                {
                    SetColor(10);
                    cout << "Congrats!!" << endl;
                    cout << "You guessed it right" << endl;
                    SetColor(1);
                    cout << "The film was : " << s << endl;
                    break;
                }

            }
            delay(5000);
            free(root);
            break;
        }
        case '3': {
            system("cls");
            string q = "WELCOME TO LINE RACING";
            zh7 = q.size();
            for (int i = 0; i < zh7; i++) //O(n)
            {
                cout << q[i];
                delay(120);
            }
            cout << endl << endl;
            char z;
            cout << "This is the 2 Player racing game based on luck,i.e throw of a dice.Each player is given a chance to roll the dice, and accordingly character is advanced in line. The player whose character reaches the end 1st, is declared as winner. " << endl << endl;
            cout << "Press any letter to continue : ";
            //cin >> z;
            z = _getch();
            system("cls");

            for (int i = 0; i < 30; i++) //O(n)
            {
                if (i == 0)
                {
                    inserte('|');
                }

                else {
                    inserte('_');
                }
            }
            for (int i = 0; i < 30; i++) //O(n)
            {
                if (i == 0)
                {
                    inserte1('|');
                }
                else {

                    inserte1('_');
                }
            }
            int count = 0;
            string s;
            string s1;
            char choose;
            SetColor(11);
            cout << "Enter name for player 1 : ";
            SetColor(1);
            getline(cin >> ws, s);
            SetColor(13);
            cout << "Press 1 to play with computer or press 2 to play with your friend\n";
            SetColor(1);
            cin >> choose;
            //choose = _getch();
            while (choose != '1' && choose != '2') //O(n)
            {
                SetColor(13);
                cout << "Press 1 to play with computer or press 2 to play with your friend\n";
                SetColor(1);
                cin >> choose;
            }
            if (choose == '2')
            {
                SetColor(11);
                cout << "Enter name for player 2 : ";
                SetColor(1);
                getline(cin >> ws, s1);

            }
            else if (choose == '1')
            {
                cout << "Computer will play with you\n ";
                s1 = "Computer";
            }


            SetColor(1);
            system("cls");
            while (1)
            {
                string s3 = "......";
                if ((count % 2) == 0)
                {
                    char ch;

                    cout << s << " , Your turn" << endl;
                    cout << "You can press 0 to quit\n";
                    do
                    {
                        cout << "Press 'y' or 'Y' to roll your dice, Press 'n' or 'N' to pass : ";
                        cin >> ch;
                    } while (ch != 'n' && ch != 'y' && ch != 'Y' && ch != 'N' && ch != '0');
                    if (ch == '0')
                    {
                        cout << "YOU QUIT\n";
                        break;
                    }
                    if (ch == 'n' || ch == 'N')
                        cout << "Your turn is passed!!" << endl;
                    if (ch == 'y' || ch == 'Y')
                    {

                        srand(time(NULL));
                        int x = rand() % 6;
                        x = x + 1;
                        cout << "Your Dice Number ";
                        for (int i = 0; i < 6; i++) //O(n)
                        {
                            delay(200);
                            cout << s3[i];
                        }
                        cout << " : " << x << endl;
                        startt = p;
                        int count1 = 1, flag1 = 0, c = 0, flag2 = 0;
                        while (p->next != NULL) //O(n)
                        {
                            count1++;
                            if (p->data == '|')
                            {
                                p->data = '_';
                                c = count1;
                                flag2 = 1;
                            }
                            else {
                                if (((x + c) == count1) && flag2 == 1)
                                {
                                    p->data = '|';
                                    flag1 = 1;
                                    break;
                                }
                            }
                            p = p->next;

                        }

                        p = startt;
                        cout << "Status of " << s << "'s line : " << endl;
                        SetColor(12);
                        display();
                        SetColor(1);
                        cout << endl;
                        cout << "Status of " << s1 << "'s line : " << endl;
                        SetColor(10);
                        display1();
                        SetColor(1);

                        if (flag1 == 0)
                        {
                            cout << "GAME OVER!!" << endl;
                            cout << s << " WON!!" << endl;
                            delay(5000);
                            break;
                        }
                        cout << endl;
                        delay(3000);
                    }
                    system("cls");
                }
                else
                {
                    if (choose == '1')
                    {
                        char ch;

                        cout << s1 << " playing..." << endl;
                        srand(time(NULL));
                        int x = rand() % 6;
                        x = x + 1;
                        cout << "Computer Dice Number ";
                        for (int i = 0; i < 6; i++) //O(n)
                        {
                            delay(200);
                            cout << s3[i];
                        }
                        cout << " : " << x << endl;
                        start1 = p1;
                        int count1 = 1, flag1 = 0, c = 0, flag2 = 0;
                        while (p1->next1 != NULL) //O(n)
                        {
                            count1++;
                            if (p1->data1 == '|')
                            {
                                p1->data1 = '_';
                                c = count1;
                                flag2 = 1;
                            }
                            else {
                                if (((x + c) == count1) && flag2 == 1)
                                {
                                    p1->data1 = '|';
                                    flag1 = 1;
                                    break;
                                }
                            }
                            p1 = p1->next1;

                        }

                        p1 = start1;
                        cout << "Status of " << s << "'s line : " << endl;
                        SetColor(12);
                        display();
                        SetColor(1);
                        cout << endl;
                        cout << "Status of " << s1 << "'s line : " << endl;
                        SetColor(10);
                        display1();
                        SetColor(1);
                        if (flag1 == 0)
                        {
                            cout << endl;
                            cout << "GAME OVER!!" << endl;
                            cout << s1 << " WON!!" << endl;
                            delay(5000);
                            break;
                        }
                        cout << endl;
                        delay(3000);
                        system("cls");
                    }
                    else if (choose == '2')
                    {
                        char ch;

                        cout << s1 << " , Your turn" << endl;
                        cout << "You can press 0 to quit\n";
                        do
                        {
                            cout << "Press 'y' or 'Y' to roll your dice, Press 'n' or 'N' to pass : ";
                            cin >> ch;

                        } while (ch != 'n' && ch != 'y' && ch != 'Y' && ch != 'N' && ch != '0');
                        if (ch == '0')
                        {
                            cout << "YOU QUIT\n";
                            break;
                        }
                        if (ch == 'n' || ch == 'N')
                            cout << "Your turn is passed!!" << endl;
                        if (ch == 'y' || ch == 'Y')
                        {

                            srand(time(NULL));
                            int x = rand() % 6;
                            x = x + 1;
                            cout << "Your Dice Number ";
                            for (int i = 0; i < 6; i++) //O(n)
                            {
                                delay(200);
                                cout << s3[i];
                            }
                            cout << " : " << x << endl;
                            start1 = p1;
                            int count1 = 1, flag1 = 0, c = 0, flag2 = 0;
                            while (p1->next1 != NULL) //O(n)
                            {
                                count1++;
                                if (p1->data1 == '|')
                                {
                                    p1->data1 = '_';
                                    c = count1;
                                    flag2 = 1;
                                }
                                else {
                                    if (((x + c) == count1) && flag2 == 1)
                                    {
                                        p1->data1 = '|';
                                        flag1 = 1;
                                        break;
                                    }
                                }
                                p1 = p1->next1;

                            }

                            p1 = start1;
                            cout << "Status of " << s << "'s line : " << endl;
                            SetColor(12);
                            display();
                            SetColor(1);
                            cout << endl;
                            cout << "Status of " << s1 << "'s line : " << endl;
                            SetColor(10);
                            display1();
                            SetColor(1);
                            if (flag1 == 0)
                            {
                                cout << endl;
                                cout << "GAME OVER!!" << endl;
                                cout << s1 << " WON!!" << endl;
                                delay(5000);
                                break;
                            }
                            cout << endl;
                            delay(3000);
                        }
                        system("cls");
                    }

                }
                count++;
            }
            p = NULL;
            p1 = NULL;
            startt = NULL;
            start1 = NULL;
            break;
        }
        case '4': {

            system("cls");
            string q = "WELCOME TO COUNTRY QUIZ";
            zh8 = q.size();
            for (int i = 0; i < zh8; i++) //O(n)
            {
                cout << q[i];
                delay(120);
            }
            cout << endl << endl;
            char z;
            cout << "This is a 2 player quiz game.\n Each person is given 5 questions to answer,\n correct answer gives 10 marks,\n wrong gives -4, \n passing fetches 0\n and correct with hint gives 7 marks.\n Person with most marks at end, wins. " << endl << endl;
            cout << "Press any letter to continue : ";
            //cin >> z;
            z = _getch();
            system("cls");

            int top = -1;
            int top1 = -1;

            char b[][30] =
            {
                "INDIA",
                "MALAYSIA",
                "JAPAN",
                "THAILAND",
                "BHUTAN",
                "INDONESIA",
                "AUSTRALIA",
                "SRI LANKA",
                "RUSSIA",
                "CHINA",
                "UKRAINE",
                "PAKISTAN",
                "EGYPT",
                "SOUTH AFRICA",
                "CANADA",
                "ENGLAND",
                "ICELAND",
                "GERMANY",
                "JAMAICA",
                "BRAZIL",
                "UNITED ARAB EMIRATES",
                "NORWAY",
                "NEW ZEALAND",
                "BANGLADESH",
                "ARGENTINA",
                "PORTUGAL",
                "VATICAN",
                "MALDIVES"
            };
            char s6[][100] =
            {

                "It is known to be worlds largest Democracy",
                "Capital of this country is Kuala Lampur",
                "Known as the Land of Rising Sun",
                "This country is home to White Elephants",
                "It is known as Land of Thunder Dragons",
                "The world's largest flower, Rafflesia Arnoldi, grows only in this country",
                "It is home to Kangaroos",
                "Has south borders with India, Home to Ravana",
                "Largest country by land",
                "World largest Population resides in this country",
                "Largest country by area in Europe (excluding Russia)",
                "Divided from India during Independence",
                "Home to Pyramids",
                "Leading producer of Platinum in the world",
                "Most Educated country in the World",
                "Only country not ruled by any other country in history",
                "Mosquito free country, known as oldest democracies",
                "Hitler ruled this country",
                "Worlds fastest Man is from this country",
                "Largest Producer of coffee",
                "World tallest building is in this Country",
                "Known as Land of Midnight Sun",
                "Famous for KIWI",
                "Got sepearted from India in 1971",
                "Name comes from the Latin word of silver",
                "Home to famous soccer player - Christiano Ronaldo",
                "Smallest country of the world",
                "Island nation in South of India, Capital is Male"

            };

            string s, s1;
            SetColor(11);
            cout << "Enter the name of Player 1 : ";
            SetColor(1);
            getline(cin >> ws, s);
            SetColor(13);
            cout << "Enter the name of Player 2 : ";
            SetColor(1);
            getline(cin >> ws, s1);
            system("cls");

            cout << s << " plays First" << endl;
            delay(2000);
            for (int i = 0; i < 5; i++) //O(n*(m+k)) "Neasted loop"
            {
                system("cls");
                srand(time(NULL));
                int x = rand() % 28;
                string s2 = s6[x];
                string s3 = b[x];
                string s4;
                int flag = 0;
                cout << "You can press 0 to quit\n";
                delay(2000);
                cout << "Your " << i + 1 << " Question is " << endl;
                cout << s2 << endl;
                cout << "Press p to pass(0 score)" << endl;
                cout << "Press h for hint( Deducts 3 points )" << endl;
                getline(cin >> ws, s4);
                if (s4 == "0")
                {
                    cout << "YOU QUIT\n";
                    top++;
                    push(0, top);
                    break;
                }

                zh9 = s4.size();
                for (int i = 0; i < zh9; i++) //O(m)
                {
                    s4[i] = toupper(s4[i]);

                }
                if (s4 == "H")
                {
                    flag = 1;
                    cout << "The name starts from : " << s3[0] << endl;
                    cout << "Enter your guess now" << endl;
                    getline(cin >> ws, s4);
                    zh9 = s4.size();
                    for (int i = 0; i < zh9; i++) //O(k)
                    {
                        s4[i] = toupper(s4[i]);

                    }


                }
                if (s4 == "P")
                {

                    top++;
                    push(0, top);

                    continue;

                }
                if (s4 == b[x] && flag == 0)
                {
                    SetColor(10);
                    cout << "Your answer is correct!!" << endl;
                    cout << "You score 10 from this one!" << endl;
                    SetColor(1);
                    top++;
                    push(10, top);
                    delay(3000);
                    continue;
                }
                if (s4 == b[x] && flag == 1)
                {
                    SetColor(6);
                    cout << "Your answer is correct, but you used a hint!!" << endl;
                    cout << "You score 7 from this one!" << endl;
                    SetColor(1);
                    top++;
                    push(7, top);
                }
                if(s4!= b[x])
                {
                    SetColor(12);
                    cout << "Sorry, your answer is wrong !!" << endl;
                    cout << "You scored a -4" << endl;
                    SetColor(1);
                    top++;

                    push(-4, top);


                }
                delay(3000);
            }
            system("cls");
            cout << s1 << " plays Now" << endl;
            delay(2000);
            for (int i = 0; i < 5; i++) //O(n*(m+k)) "Neasted loop"
            {
                system("cls");

                srand(time(NULL));
                int x = rand() % 28;
                string s2 = s6[x];
                string s3 = b[x];
                string s4;
                int flag = 0;
                cout << "You can press 0 to quit\n";
                cout << "Your " << i + 1 << " Question is " << endl;
                cout << s2 << endl;
                cout << "Press p to pass(0 score)" << endl;
                cout << "Press h for hint( Deducts 3 points )" << endl;
                getline(cin >> ws, s4);
                if (s4 == "0")
                {
                    cout << "YOU QUIT\n";
                    break;
                }
                zh10 = s4.size();
                for (int i = 0; i < zh10; i++) //O(m)
                {
                    s4[i] = toupper(s4[i]);

                }
                if (s4 == "H")
                {
                    flag = 1;
                    cout << "The name starts from : " << s3[0] << endl;
                    cout << "Enter your guess now" << endl;
                    getline(cin >> ws, s4);
                    zh11 = s4.size();
                    for (int i = 0; i < zh11; i++) //O(k)
                    {
                        s4[i] = toupper(s4[i]);

                    }

                }
                if (s4 == "P")
                {
                    top1++;
                    push1(0, top1);
                    continue;

                }
                if (s4 == b[x] && flag == 0)
                {
                    SetColor(10);
                    cout << "Your answer is correct!!" << endl;
                    cout << "You score 10 from this one!" << endl;
                    SetColor(1);
                    top1++;
                    push1(10, top1);
                    delay(3000);
                    continue;

                }
                if (s4 == b[x] && flag == 1)
                {
                    SetColor(6);
                    cout << "Your answer is correct, but you used a hint!!" << endl;
                    cout << "You score 7 from this one!" << endl;
                    SetColor(1);
                    top1++;

                    push1(7, top1);
                }
                else {
                    SetColor(12);
                    cout << "Sorry, your answer is wrong !!" << endl;
                    cout << "You scored a -4" << endl;
                    SetColor(1);
                    top1++;
                    push1(-4, top1);

                }
                delay(3000);
            }
            system("cls");

            int sum = 0, sum1 = 0;
            for (int j = 0; j < 5; j++) //O(n)
            {

                sum += pop(top);
                top--;
                sum1 += pop1(top1);
                top1--;

            }
            string s7 = "......";
            if (sum > sum1)
            {
                cout << "The scores are : " << endl;
                cout << s << " scores ";
                for (int i = 0; i < 6; i++) //O(n)
                {
                    delay(200);
                    cout << s7[i];
                }
                cout << sum << endl;
                cout << s1 << " scores ";
                for (int i = 0; i < 6; i++) //O(n)
                {
                    delay(200);
                    cout << s7[i];
                }
                cout << sum1 << endl;
                SetColor(10);
                cout << s << " WINS" << endl;
                SetColor(1);

            }
            else
                if (sum < sum1)
                {
                    cout << "The scores are : " << endl;
                    cout << s << " scores ";
                    for (int i = 0; i < 6; i++) //O(n)
                    {
                        delay(200);
                        cout << s7[i];
                    }
                    cout << sum << endl;
                    cout << s1 << " scores ";
                    for (int i = 0; i < 6; i++) //O(n)
                    {
                        delay(200);
                        cout << s7[i];
                    }
                    cout << sum1 << endl;
                    SetColor(10);
                    cout << s1 << " WINS" << endl;
                    SetColor(1);

                }
                else {
                    SetColor(6);
                    cout << "ITS A DRAW!!" << endl;
                    SetColor(1);
                    cout << "Both score : " << sum << endl;
                }

            st.s[5] = { 0 };
            st1.s1[5] = { 0 };

            delay(3000);


            break; }

        case '5':
        {
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<seconds>(stop - start);
            cout << "\nTime taken : " << duration.count() << " seconds";
            delay(3000);
            break;
        }
        case '6': {
            system("cls");
            exit(0); }
        default:break;

        }


    } while (1);

    //return 0;

}
void board()//define the board drawing mechanism!
{
    cout << "----------------------------------------------------------------------------" << endl << endl;
    cout << squares[100] << "\t" << squares[99] << "\t" << squares[98] << "\t" << squares[97] << "\t" << squares[96] << "\t"
        << squares[95] << "\t" << squares[94] << "\t" << squares[93] << "\t" << squares[92] << "\t" << squares[91] << endl << endl;

    cout << squares[81] << "\t" << squares[82] << "\t" << squares[83] << "\t" << squares[84] << "\t" << squares[85] << "\t"
        << squares[86] << "\t" << squares[87] << "\t" << squares[88] << "\t" << squares[89] << "\t" << squares[90] << endl << endl;

    cout << squares[80] << "\t" << squares[79] << "\t" << squares[78] << "\t" << squares[77] << "\t" << squares[76] << "\t"
        << squares[75] << "\t" << squares[74] << "\t" << squares[73] << "\t" << squares[72] << "\t" << squares[71] << endl << endl;

    cout << squares[61] << "\t" << squares[62] << "\t" << squares[63] << "\t" << squares[64] << "\t" << squares[65] << "\t"
        << squares[66] << "\t" << squares[67] << "\t" << squares[68] << "\t" << squares[69] << "\t" << squares[70] << endl << endl;

    cout << squares[60] << "\t" << squares[59] << "\t" << squares[58] << "\t" << squares[57] << "\t" << squares[56] << "\t"
        << squares[55] << "\t" << squares[54] << "\t" << squares[53] << "\t" << squares[52] << "\t" << squares[51] << endl << endl;
    cout << squares[41] << "\t" << squares[42] << "\t" << squares[43] << "\t" << squares[44] << "\t" << squares[45] << "\t"
        << squares[46] << "\t" << squares[47] << "\t" << squares[48] << "\t" << squares[49] << "\t" << squares[50] << endl << endl;

    cout << squares[40] << "\t" << squares[39] << "\t" << squares[38] << "\t" << squares[37] << "\t" << squares[36] << "\t"
        << squares[35] << "\t" << squares[34] << "\t" << squares[33] << "\t" << squares[32] << "\t" << squares[31] << endl << endl;

    cout << squares[21] << "\t" << squares[22] << "\t" << squares[23] << "\t" << squares[24] << "\t" << squares[25] << "\t"
        << squares[26] << "\t" << squares[27] << "\t" << squares[28] << "\t" << squares[29] << "\t" << squares[30] << endl << endl;

    cout << squares[20] << "\t" << squares[19] << "\t" << squares[18] << "\t" << squares[17] << "\t" << squares[16] << "\t"
        << squares[15] << "\t" << squares[14] << "\t" << squares[13] << "\t" << squares[12] << "\t" << squares[11] << endl << endl;

    cout << squares[1] << "\t" << squares[2] << "\t" << squares[3] << "\t" << squares[4] << "\t" << squares[5] << "\t"
        << squares[6] << "\t" << squares[7] << "\t" << squares[8] << "\t" << squares[9] << "\t" << squares[10] << endl << endl;
    cout << "----------------------------------------------------------------------------" << endl;
}

int roll_dice()//define the dice rolling mechanism
{
    return rand() % (7 - 1) + 1;//can only roll 1 - 6
}

int check_progress()//define the progress checking mechanism
{
    if (squares[100] == 200 || squares[100] == 300)
    {
        return 1;//game has ended... win! someone has
    }
    else
    {
        return 0;//game is still on, win no one has...
    }
}



