#include "game.h"

void print_game_rules(void)
{
    printf("\nA player rolls two dice. Each die has six faces. \nThese faces contain 1, 2, 3, 4, 5, and 6 spots. \nAfter the dice have come to rest, the sum of the spots on the two upward faces is calculated. \nIf the sum is 7 or 11 on the first throw, the player wins. \nIf the sum is 2, 3, or 12 on the first throw (called 'craps'), the player loses (i.e. the 'house' wins). \nIf the sum is 4, 5, 6, 8, 9, or 10 on the first throw, then the sum becomes the player's 'point.' \nTo win, you must continue rolling the dice until you 'make your point.' \nThe player loses by rolling a 7 before making the point.\n\n");
}
int runmenu(void)
{
    int option = 0;
    printf("\nMAIN MENU\n");
    printf("\n1. Rules for game of craps\n");
    printf("2. Play New Game \n");
    printf("3. Continue playing game (If game has already been started) \n");
    printf("4. Exit \n");
    scanf("%d", &option);
    return option;
}
double get_bank_balance(void)
{
    double balance = 0.0;
    printf("Enter initial bank balance from which wages will be added or subtracted from\n");
    scanf("%lf", &balance);
    return balance;
}
double get_wager_amount(void)
{
    double wager = 0.0;
    printf("Enter in wager for this roll\n");
    scanf("%lf", &wager);
    return wager;
}
double check_wager_amount(double wager, double bankbalance)
{
    int checkwager = 0;
    double overdraft = 0.0;
    overdraft = bankbalance - wager;
    while (overdraft < 0)
    { 
        printf("That wager exceeds the balance in your bank account\n");
        wager = get_wager_amount();
        overdraft = bankbalance - wager;
    }
        return wager;

}
//int get_new_wager(int checkwager, double wager, double bankbalance)
//{
//    
//    while (checkwager == 0)
//    {
//        
//        wager = get_wager_amount();
//        checkwager = check_wager_amount(wager, bankbalance);
//    }
//    return wager;
//}
int roll_die(void)
{
    int die = 0, chance = 0, bob = 0, bob1 = 0, bob2 =0;

    srand((unsigned int)time(NULL));
  /*  bob1 = rand();
    srand((unsigned int)time(NULL));
    bob2 = rand();
    bob = bob1 * bob2;*/

    //chance = rand() % 2 + 1;
    //if (chance == 0)
    die = rand() % 6 + 1;
   /* else
    die = rand() % 6 + 1;*/
    return die;
}
int calculate_sum_dice(int die1_value, int die2_value)
{
    int sum = 0;
    sum = die1_value + die2_value;
    return sum;
}
int is_win_loss_or_point(int sum_dice)
{
    if (sum_dice == 7 || sum_dice == 11)
        return 1; //player wins
    else if (sum_dice == 2 || sum_dice == 3 || sum_dice == 12)
        return 0; //player loses
    else if (sum_dice <= 12 && sum_dice >= 2)
        return -1; //player point
    return 99; //error checking
}
void random(unsigned int milliseconds)
{
    Sleep(milliseconds);
}
int is_point_loss_or_neither(int sum_dice, int point_value)
{
    if (sum_dice == point_value)
        return 1; //player win
    else if (sum_dice == 7)
        return 0; //player lost
    else
        return -1; //need to roll again (not condition 1 or 2)
}
double adjust_bank_balance(double bank_balance, double wager_amount, int add_or_subtract)
{
    if (add_or_subtract == 1) // If they won, add wager
        bank_balance += wager_amount;
    else if (add_or_subtract == 0) //IF they lost, take away wager
        bank_balance -= wager_amount;
    return bank_balance;
}
void chatter_messages(int number_rolls, int win_loss_neither, double initial_bank_balance, double current_bank_balance, double wager)
{
    /*if (win_loss_neither == 0)
        printf("Sorry, you busted!");
    else if (win_loss_neither == 1)
        printf("nice roll");*/
    if (initial_bank_balance > 1000)
    {
        printf("\nDeep pockets eh?\n\n");
    }
    else if (current_bank_balance < 50)
        printf("\nOh, you're going for broke, huh?\n\n");
    else if (wager<10)
        printf("\nAw cmon, take a chance!\n\n");
    else if (current_bank_balance > 10000)
    {
        printf("\nYou're up big, now's the time to cash in your chips!\n\n");
    }
    else if (number_rolls >= 16)
    {
        printf("\nLong game ain't it!\n\n");
    }
}
int yourbroke(double bankbalance, int *newgame)
{
    int continueplaying = 0;
        if (bankbalance <= 0)
        {
            printf("You have gone broke!\n");
            //*newgame = 1;
            return 2;
        }
        if (bankbalance > 0)
        {
            continueplaying = wanttocontinue();
            return continueplaying;

        }

   
}
int wanttocontinue(void)
{
    int continueplaying = 0;
    printf("\nWould you like to play again?\n");
    printf("If yes, please enter a 0, if you would like to view the menu again, enter a 1\n");
    printf("If you would like to exit, please enter any other number.");
    scanf("%d", &continueplaying);
    return continueplaying;
}

