/*
Programmer: Benjamin Michaelis
Program: A Chance Game of Craps
Date: 2/19/2020
Description: This program will allow a user to play a game of the dice game craps
*/

#include "game.h"

int main(void)
{
    int checkwager = 0, diecount = 0, die1 = 0, die2 = 0,
        dice_sum = 0, winlosspoint = 0, errorcheck = 0,
        continueplaying = 0, playerspoint = 0, pointlossneither = 0,
        option = 0, newgame = 0, count = 0, number_rolls = 0, recount = 0;
    double initialbankbalance = 0.0, bankbalance = 0.0, wager = 0.0;
        
    do
    {
        do
        {
            option = runmenu();//get user input from menu
        } while (option < 1 || option > 4);//keep showing menu until they enter option between 1 and 4
        if (option == 2) //if they want to start a brand new game - get new bank balance to start over
        {
            newgame = 1;
        }
        if (option == 3 && recount >= 1) //if they have played at least once, don't get new bank balance if they want to continue
        {
            option = 2;
        }
        if (option == 3 && recount == 0) //if they accidently hit 3 and they haven't started a new game yet, start a new game for them
        {
                newgame = 1;
                option = 2;
        }
        continueplaying = 0;//allow them to continue looping in the future in case they want to just play again, and to loop back to main menu after just printing game rules
        switch (option)
        {
        case 1: printf("\nRules for the Dice Game of Craps : \n");
            print_game_rules(); // print rules for the game of craps
            break;

        case 2:
            if (newgame == 1)
            {
                initialbankbalance = get_bank_balance();
                bankbalance = initialbankbalance;
                count = 1;
                newgame = 0;
            }
            for (count = 0; continueplaying == 0; count++)
            {
                continueplaying = 0;
                wager = get_wager_amount();//initial wager
                wager = check_wager_amount(wager, bankbalance);
                chatter_messages(number_rolls, pointlossneither, initialbankbalance, bankbalance, wager);
                initialbankbalance = 0;
                die1 = roll_die();// maybe put these within calculate sum declaration itself??
                random(1000); // create more randomness between die rolls due to time continuing
                die2 = roll_die();
                number_rolls += 2;
                dice_sum = calculate_sum_dice(die1, die2);
                winlosspoint = is_win_loss_or_point(dice_sum);
                if (winlosspoint == 99) // if there is an error (dice sum rolling above 12)
                {
                    for (errorcheck; errorcheck <= 2; errorcheck += 1)
                    {
                        printf("Error in dice rolling, retrying\n");
                    }
                    printf("This game of craps has a repeating error, if it continues, please contact designer\n");
                    return 99;
                }
                else if (winlosspoint == 1) //player wins
                {
                    printf("You have rolled a %d and a %d for a sum of %d and WON THE GAME! \nCongratulations, you have won your wager of %lf! It as been added to your bank balance!\n", die1, die2, dice_sum, wager);
                    bankbalance = adjust_bank_balance(bankbalance, wager, 1);
                    printf("Your new bank balance is: %lf\n", bankbalance);
                    continueplaying = yourbroke(bankbalance, &newgame);// check if you have gone broke (bank balance = 0)
                    
                }
                else if (winlosspoint == 0) //player loses
                {
                    printf("You have rolled a %d and a %d for a sum of %d and lost the game. \nYour wager of %lf has been lost and subtracted from your bank balance.\n",die1, die2, dice_sum, wager);
                    bankbalance = adjust_bank_balance(bankbalance, wager, 0);
                    printf("Your new bank balance is: %lf\n", bankbalance);
                    continueplaying = yourbroke(bankbalance, &newgame); // check if you have gone broke (bank balance = 0) and if not if you want to play again
                    
                }
                else if (winlosspoint == -1) //sum becomes players point and roll again
                {
                    playerspoint = dice_sum;
                    pointlossneither = -1;

                    printf("You have rolled a %d and a %d for a sum of %d so your roll now is your point that you have to roll in order to win!\n", die1, die2, dice_sum);
                    while (pointlossneither == -1)
                    {
                        die1 = roll_die();//maybe put these within calculate sum declaration itself??
                        random(1000);
                        die2 = roll_die();
                        dice_sum = calculate_sum_dice(die1, die2);
                        pointlossneither = is_point_loss_or_neither(dice_sum, playerspoint);
                    }
                    if (pointlossneither == 1)
                    {
                        printf("You have rolled a %d and a %d for a sum of %d. This means you have rolled your point of %d! \nCongratulations, you have won your wager of %lf! It as been added to your bank balance!\n", die1, die2, dice_sum, playerspoint, wager);
                        bankbalance = adjust_bank_balance(bankbalance, wager, 1);
                        printf("Your new bank balance is: %lf\n", bankbalance);
                        continueplaying = yourbroke(bankbalance, &newgame);// check if you have gone broke (bank balance = 0)
                        
                    }
                    else if (pointlossneither == 0)
                    {
                        printf("You have rolled a %d and a %d for a sum of 7, and have lost the game. \nYour wager of %lf has been lost and subtracted from your bank balance\n", die1, die2, wager);
                        bankbalance = adjust_bank_balance(bankbalance, wager, 0);
                        printf("Your new bank balance is: %lf\n", bankbalance);
                        continueplaying = yourbroke(bankbalance, &newgame);// check if you have gone broke (bank balance = 0)
                        

                    }
                   
                }
                recount++;//have they played at least once? if so, if they hit continue game from menu, save current bankbalance
                if (continueplaying == 1)
                {
                    continueplaying = 0;//allows them to loop back to main menu
                    break;
                }
                if (continueplaying == 2) // if you have gone broke, send to main menu and force to start new game if they hit 3 for continue game even (can't continue because they are broke in current game, would error loop)
                {
                    continueplaying = 0;//allows them to loop back to main menu
                    newgame = 1; //gets new initial bank balance again since they have to start new game
                    break;
                }
                
            }

            break;
        case 4:
            continueplaying = 9;//breaks them out of do while loop to exit game
            break;
        }

    } while (continueplaying == 0);
       
    
    printf("\nThank you for playing this dice game!\n\n");
    
    
    
    return 0;
}
