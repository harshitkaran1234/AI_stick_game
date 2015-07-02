#include <iostream> 
#include <map>	//std::map 
#include <list> //std::list
#include <vector> //std::vector
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std; 


// used to make sure that player enters number between 1 and 3 inclusive
int remove(int num) {
	int flag = 0 ; 
	int ret;
	while (flag == 0) 
	{
		cout << "Player" << num << ": How many sticks do you remove (1-3)?"; 
		cin >> ret; 
		if (ret >=1 && ret <= 3) 
		{
			flag =1;

		}
	}
	return ret; 
}

// used to ask for stick number
int stick_ask() {
	// let user enter amount of sticks
	int flag1 = 0 ; 
	int stick_amount; 
	// make sure that the user enters a value between 10 and 100 inclusive 
	while (flag1 == 0 ) 
	{
		cout << "How many sticks are there on the table initially (10-100)?" ; 
		
		cin >> stick_amount; 
		if (stick_amount >= 10 && stick_amount <=100) 
		{
			flag1 = 1; 
		}
	}
	return stick_amount; 
}

//used to check if remove causes a negative number
int player_remove(int total, int player) {
 		int ret; 
		int flag2 = 0 ; 
		// check if can after removal if the value is neg
		while (flag2 == 0 ) 
		{
			ret = remove(player);
			int temp;  
			temp = total-ret; 
			if ( temp >= 0 ) 
			{
				flag2 = 1;  
			}
		}
		return ret; 

}


//used to check if remove causes a neg number for AI 
bool AI_remove(int total, int val_rm) {
		int temp = total-val_rm; 
		if (temp >= 0) 
			return true; 
		else
			return false;
}


//ask for play style; 
int style() {
	int flag = 0 ; 
	int ret;
	while (flag == 0) 
	{
		cout << "Enter Here: " ; 
		cin >> ret; 
		if (ret >=1 && ret <= 3) 
		{
			flag =1;

		}
	}
	return ret; 
}

// ask user if user wants to play again
bool play_again() {
	string temp_string; 
	int flag = 0 ; 
	while (flag == 0 ) 
	{
		cout << "Do you want to play again? [y/n]" ; 
		cin >> temp_string; 
		if (temp_string == "y")
		{
			return true; 
		} 
		if (temp_string == "n") 
		{
			return false; 
		}
	}

}


int AI_play(map<int, list<int> > & AI_map, map<int, list<int> > & temp_AI_map, list<int>  & temp_list, int & stick_amount ) 
{
	// loop initialization
	int rm_flag_2 = 0; 
	list<int>::iterator it;
	int total_elem; 
	int list_index; 
	int rm_temp; 
				

	// loop until get a number that is playable
				
	while(rm_flag_2 == 0) 
	{
		// iterator 
		it = AI_map[stick_amount].begin(); 
		//get the total number of elements 
		total_elem = AI_map[stick_amount].size(); 
		// generate random number within index
		list_index = rand()%total_elem; 
		//cout << "RAND ELEM: " << list_index; 
				
		// update iterator
		for (int i= 0 ; i < list_index; i++) 
			it++;  
	
		// save value that is going to be removed
		rm_temp = *it; 
		//cout << "   Value : " << rm_temp << endl; 

		// check if valid value 
		// check if can after removal if the value is neg
				
		int temp;  
		temp = stick_amount-rm_temp; 
		if ( temp >= 0 ) 
		{
			rm_flag_2 = 1;  
		}

	}
				
	//remove number from list
	AI_map[stick_amount].erase(it); 
				
	
	//put number into temp map 
	temp_AI_map[stick_amount].push_back(rm_temp);

	//creating a temp list to save the indices 
	temp_list.push_back(stick_amount); 
			
	// actually subtract the value from the total 
	stick_amount = stick_amount-rm_temp; 

	// return rm_temp for printing out
	return rm_temp; 

}



int main(){
	
	cout << "Welcome to the game of sticks!" << endl; 


	cout << "Select an option:" << endl << "1)human vs. human" << endl << "2)human vs. AI" << endl << "3) human vs. pre-trained AI" << endl; 
	int choice = style(); 
	
	 

	if ( choice ==1) 
	{


	// ask for stick amount; 
	int stick_amount = stick_ask(); 

	int win = 0 ;
	int player = 1;  

	//while loop until someone wins 
	while (win == 0 ) 
	{		
		cout << "There are " << stick_amount << " sticks left. " << endl;
	
		int val = player_remove(stick_amount, player); 
		stick_amount = stick_amount-val; 
		
		//check if player lost 
		if (stick_amount == 0 ) 
		{
			// print out winner and loser 
			cout << "Player " << player << " Lost!" << endl; 
			if (player == 1) 
			{
				win = 2; 
			}
			else 
			{
				win = 1; 
			}
			cout << "Player " << win << " Won :) " << endl; 
		}


		//switch player 
		if (player ==1 ) 
			player = 2; 
		else
			player =1; 

		cout << endl; 

	}

	}

	if (choice == 2) 
	{
		// initialization for AI 
		// creating AI map 
		map<int, list<int> > AI_map; 
		for (int i = 1 ; i<= 100; i ++) 
		{
			AI_map[i].push_back(1); 
			AI_map[i].push_back(2);
			AI_map[i].push_back(3);
		}
	
		

		// printing out map
		/*
		for (int i = 1; i<=100 ; i++) 
		{
			cout << "Number: " << i << "   " ; 
			for (list<int>::iterator it = AI_map[i].begin(); it != AI_map[i].end(); it++) 
			{
				cout << *it << " " ; 
			}
			cout << endl; 
		}*/
		bool again = true; 
		while (again == true)
		{
		
		/*for (int i = 1; i<=10 ; i++) 
		{
			cout << "Number: " << i << "   " ; 
			for (list<int>::iterator it = AI_map[i].begin(); it != AI_map[i].end(); it++) 
			{
				cout << *it << " " ; 
			}
			cout << endl; 
		}*/


		// ask for stick amount; 
		int stick_amount = stick_ask();

				
		cout << "Computer will be player two" << endl; 
		cout << "Randomly selecting player to start first ..."<<endl; 
		int win = 0 ;
		//randoms who starts first 
		srand(time(NULL)); 
		int player = rand()%2+1;  
		cout << "Player " << player << " starts" << endl; 	


		// initialization for game 

		// initialization of temp AI map 
		map<int, list<int> > temp_AI_map ; 
		// initialization of temp indices vector
		list<int> temp_list ; 


		//while loop until someone wins 
		while (win == 0 ) 
		{		
			cout << "There are " << stick_amount << " sticks left. " << endl;
			if (player == 1) 
			{
				int val = player_remove(stick_amount, player); 
				stick_amount = stick_amount-val; 
			}

			if (player == 2)
			{
				int rm_temp; 
				rm_temp = AI_play(AI_map, temp_AI_map, temp_list, stick_amount); 
				cout << "Computer: How many sticks do you remove (1-3)?" << rm_temp << endl;
			}


			//check if player lost 
			if (stick_amount == 0 ) 
			{
				// print out winner and loser 
				cout << "Player " << player << " Lost!" << endl; 
				if (player == 1) 
				{
					win = 2; 
				}
				else 
				{
					win = 1; 
				}
				cout << "Player " << win << " Won :) " << endl; 
			}


			//switch player 
			if (player ==1 ) 
				player = 2; 
			else
				player =1; 

			cout << endl; 
		 
		}


		int AI_learn_int; 
		// AT THE END OF THE GAME 
		// IF AI WON ; add all numbers in indices back into AI_map
		if (win == 2) 
		{	
			AI_learn_int = 2; 
		}
		// IF AI LOST; add back the numbers once 
		if (win == 1) 
		{
			AI_learn_int = 1; 
		}

		//add back numbers into AI_map
		while (temp_list.empty() == false) 
		{	
				// get index and remove the index
				int temp_index = temp_list.front(); 
				temp_list.pop_front(); 
				// get the value 
				int temp_val = temp_AI_map[temp_index].front(); 
				// add back in once or twice depending on win or lost 
				for (int i= 0 ; i < AI_learn_int; i ++) 
				{
					AI_map[temp_index].push_back(temp_val); 
				}
		}
		
		again = play_again(); 
		
		}

	}


	if (choice == 3) 
	{
		cout << "Training AI ..... " << endl; 
		srand(time(NULL)); 
		// initialization for AI 
		// creating AI map 1
		map<int, list<int> > AI_map; 
		for (int i = 1 ; i<= 100; i ++) 
		{
			AI_map[i].push_back(1); 
			AI_map[i].push_back(2);
			AI_map[i].push_back(3);
		}

		


		//creating AI map 2
		map<int, list<int> > AI_map_2; 
		for (int i = 1 ; i<= 100; i ++) 
		{
			AI_map_2[i].push_back(1); 
			AI_map_2[i].push_back(2);
			AI_map_2[i].push_back(3);
		}

		

		// amount of training 
		int train_time = 10000; 

		while (train_time > 0 ) 
		{

			// initialization of temp AI map 
			map<int, list<int> > temp_AI_map ; 
			// initialization of temp indices vector
			list<int> temp_list ; 

			// initialization of temp AI map 
			map<int, list<int> > temp_AI_map_2 ; 
			// initialization of temp indices vector
			list<int> temp_list_2 ; 

			
			// game set up  	 
			int com_player = rand()%2+1; 
			//cout << "Player " << com_player << "starts first " << endl; 
			int stick_amount = rand()%91+10; 
			//int stick_amount = rand()%10+1; 
			//cout << "initial stick amount : " << stick_amount << endl;  
			int AI_win = 0; 
			while (AI_win == 0 )
			{	
				//cout << "stick amount : " << stick_amount << endl;  
				// let com player play the game 
				if (com_player == 1) 
				{
					//cout << "pre COM1 play " << endl; 
					int temp1 = AI_play(AI_map, temp_AI_map, temp_list, stick_amount); 
					//cout << "COM1 : " << temp1 << endl; 
				}
				else
				{
					//cout << "pre COM2 play " << endl; 
					int temp2 = AI_play(AI_map_2, temp_AI_map_2, temp_list_2, stick_amount); 
					//cout << "COM2 : " << temp2 << endl; 
				}

				//check if player lost 
				if (stick_amount == 0 ) 
				{
					if (com_player == 1) 
					{
						AI_win = 2; 
					}
					else 
					{
						AI_win = 1; 
					}
				}


				//switch player 
				if (com_player ==1 ) 
					com_player = 2; 
				else
					com_player =1; 
			}
			//cout << "GAME END " << efndl; 
			
			int AI_learn_int; 
			// AT THE END OF THE GAME 
			// IF AI WON ; add all numbers in indices back into AI_map
			if (AI_win == 1) 
				AI_learn_int = 2; 
			else
				AI_learn_int = 1; 

			//add back numbers into AI_map
			while (temp_list.empty() == false) 
			{	
				// get index and remove the index
				int temp_index = temp_list.front(); 
				temp_list.pop_front(); 
				// get the value 
				int temp_val = temp_AI_map[temp_index].front(); 
				// add back in once or twice depending on win or lost 
				for (int i= 0 ; i < AI_learn_int; i ++) 
				{
					//cout << "COM1: index: " << temp_index << "  val : " << temp_val << endl; 
					AI_map[temp_index].push_back(temp_val); 
				}
			}


			//add back numbers into AI_map_2
			while (temp_list_2.empty() == false) 
			{	
				// get index and remove the index
				int temp_index = temp_list_2.front(); 
				temp_list_2.pop_front(); 
				// get the value 
				int temp_val = temp_AI_map_2[temp_index].front(); 
				// add back in once or twice depending on win or lost 
				for (int i= 0 ; i < AI_win; i ++) 
				{
					//cout << "COM2: index: " << temp_index << "  val : " << temp_val << endl; 
					AI_map_2[temp_index].push_back(temp_val); 
				}
			}


			train_time--; 


			//cout << train_time << endl; 
		}


		/*
		for (int i = 1; i<=100 ; i++) 
		{
			cout << "Number: " << i << "   " ; 
			for (list<int>::iterator it = AI_map[i].begin(); it != AI_map[i].end(); it++) 
			{
				cout << *it << " " ; 
			}
			cout << endl; 
		}*/
			
		/*
		for (int i = 1; i<=10 ; i++) 
		{
			cout << "Number: " << i << "   " ; 
			for (list<int>::iterator it = AI_map_2[i].begin(); it != AI_map_2[i].end(); it++) 
			{
				cout << *it << " " ; 
			}
			cout << endl; 
		}
		*/
		bool again = true; 
		while (again == true)
		{


		// ask for stick amount; 
		int stick_amount = stick_ask();

				
		cout << "Computer will be player two" << endl; 
		cout << "Randomly selecting player to start first ..."<<endl; 
		int win = 0 ;
		//randoms who starts first 
		srand(time(NULL)); 
		int player = rand()%2+1;  
		cout << "Player " << player << " starts" << endl; 	


		// initialization for game 

		// initialization of temp AI map 
		map<int, list<int> > temp_AI_map ; 
		// initialization of temp indices vector
		list<int> temp_list ; 


		//while loop until someone wins 
		while (win == 0 ) 
		{		
			cout << "There are " << stick_amount << " sticks left. " << endl;
			if (player == 1) 
			{
				int val = player_remove(stick_amount, player); 
				stick_amount = stick_amount-val; 
			}

			if (player == 2)
			{
				int rm_temp; 
				rm_temp = AI_play(AI_map, temp_AI_map, temp_list, stick_amount); 
				cout << "Computer: How many sticks do you remove (1-3)?" << rm_temp << endl;
			}


			//check if player lost 
			if (stick_amount == 0 ) 
			{
				// print out winner and loser 
				cout << "Player " << player << " Lost!" << endl; 
				if (player == 1) 
				{
					win = 2; 
				}
				else 
				{
					win = 1; 
				}
				cout << "Player " << win << " Won :) " << endl; 
			}


			//switch player 
			if (player ==1 ) 
				player = 2; 
			else
				player =1; 

			cout << endl; 
		 
		}


		int AI_learn_int; 
		// AT THE END OF THE GAME 
		// IF AI WON ; add all numbers in indices back into AI_map
		if (win == 2) 
		{	
			AI_learn_int = 2; 
		}
		// IF AI LOST; add back the numbers once 
		if (win == 1) 
		{
			AI_learn_int = 1; 
		}
		

		//add back numbers into AI_map
		while (temp_list.empty() == false) 
		{	
				// get index and remove the index
				int temp_index = temp_list.front(); 
				temp_list.pop_front(); 
				// get the value 
				int temp_val = temp_AI_map[temp_index].front(); 
				// add back in once or twice depending on win or lost 
				for (int i= 0 ; i < AI_learn_int; i ++) 
				{
					AI_map[temp_index].push_back(temp_val); 
				}
		}

		again = play_again(); 
		
		}


	}
	return 0; 

}


