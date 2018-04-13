#include <iostream>
#include <string>

class VendingMachine {

	private:
		// Establishing the items in the vending machine in the same order as their quanitites and prices
		std::string items[6] = {"candy", "snack", "nuts", "Coke", "Pepsi", "Gingerale"};

		float price[6] = {0.10, 0.50, 0.90, 0.25, 0.35, 0.45};
		
		int quantity[6];

		// Establishing system cash which indicates how much money is present in the vending machine
		int systemCash[6];

		// Maintains a record of denominations of coins inserted for a transaction by a user
		int insertedCash[6];

		// Sequence of items selected from the vending machine, with each index holding the frequency of selection
		int itemsToBuy[6];

		void display(){
			//iterate through the inventory
			std::cout<<"\n";
			for(int i=0;i<6;i++){
				std::cout<<"ITEM "<<i+1<<": "<<items[i]<<" currently "<< quantity[i] <<" in stock"<<"\n";
			}
			std::string opt;
			int num;

			//initialized to 0
			int i=0;
			while(i!=7){
				itemsToBuy[i]= 0; 
				i++;
			}
			opt = "Y";

			//Increments the frequency of each item chosen
			while(opt=="Y" || opt=="y"){
				std::cout<<"\n\nEnter serial number to add item to cart\n";
				std::cin>>num;
				if((itemsToBuy[num-1]+1)>quantity[num-1]){
					std::cout<<" Item out of stocks and cannot be added, please proceed to checkout or add other items to cart";
				}
				else{
					itemsToBuy[num-1]++;
				}
				std::cout<<"\nEnter Y to select more items. To end your order or cancel type N \n";
				std::cin>>opt;
			}
		}

		// calculates total price of the items selected
		float calculateTotalPrice(){
		    float totalCost = 0.0;
		    int i=0;
		    while(i<7){
		   		switch(i){
		   			case 0 : totalCost+= itemsToBuy[i]* price[i]; break;
		   			case 1 : totalCost+= itemsToBuy[i]* price[i]; break;
		   			case 2 : totalCost+= itemsToBuy[i]* price[i]; break;
	    				case 3 : totalCost+= itemsToBuy[i]* price[i]; break;
	      				case 4 : totalCost+= itemsToBuy[i]* price[i]; break;
		   			case 5 : totalCost+= itemsToBuy[i]* price[i]; break;
	    		}
	    		i++;
			}
			std::cout<<totalCost<<"\n";
			return totalCost;
		}

		// confirms status of checkout with the User
		bool confirmOrder(float totalCost) {
			std::string opt;
			std::cout<<"\nThe total cost amounts to $"<<totalCost<<" for the items. Please type Y to confirm: \n";
			std::cin>>opt;
			if(opt=="y" || opt=="Y"){
				return true;
			}
			else {
				return false;
			}
		}


		// retrieves a selection of penny,nickel,dime, quart, $1, $2 bills from the user
		float getMoneyFromConsumer(){
			float calculatedCash;
			int i = 0;
			int valueOfDenomination = 0;
			std::cout<<"\n Please insert cash in counts of penny, nickel, dime, quart, $1 bill, $2 bill in this specific order. Eg 1 <enter> 1 <enter> 1 \n";
			while(i<6){
				std::cin>> valueOfDenomination;

				//updates the value of insert Cash with frequency of coins inserted by the user
				insertedCash[i]=valueOfDenomination;
				switch(i){
					case 0 : calculatedCash += 0.01 * valueOfDenomination; break;
					case 1 : calculatedCash += 0.05 * valueOfDenomination; break;
					case 2 : calculatedCash += 0.10 * valueOfDenomination; break;
					case 3 : calculatedCash += 0.25 * valueOfDenomination; break;
					case 4 : calculatedCash += 1.00 * valueOfDenomination; break;
					case 5 : calculatedCash += 2.00 * valueOfDenomination; break;
				}
				i++;
			}
			std::cout<<"Calcuated cash: "<<calculatedCash<<"\n";
			return calculatedCash;
		}

		// Items have been successfully vended and user gets a confirmation message
		void vendItems(){
			for(int i=0;i<6;i++){
				if (itemsToBuy[i]!=0){
					std::cout<<"You purchased "<<itemsToBuy[i]<<" of "<<items[i]<<"\n";
					// stocks inventory is updated accordingly
					quantity[i]-=itemsToBuy[i];
				}
			}
		}


		// difference amount is returned to the user after updating it within the system cash, i.e. currency held by the Vending Machine
		void returnCash(float difference){
			

			int diff = difference*100;
			int index[6] = {1, 5, 10, 25, 100, 200};

			int cashDenominations[6] = {0, 0, 0, 0, 0, 0};
			int i=5;
			while(diff > 0) {
				if ((diff >= index[i]) && (systemCash[i] > 0)) {
					cashDenominations[i]++;
					systemCash[i]--;
					diff-=index[i];
				}
				else {
					i--;
				}
			}

			i=0;
			while(i<6){
				switch(i){
					case 0 : std::cout<<cashDenominations[i]<< " Pennies \n" ; break;
	    				case 1 : std::cout<<cashDenominations[i]<< " Nickels \n" ; break;
				    	case 2 : std::cout<<cashDenominations[i]<< " Dimes \n" ; break;
				    	case 3 : std::cout<<cashDenominations[i]<< " Quarts \n" ; break;
				    	case 4 : std::cout<<cashDenominations[i]<< " $1 Bills \n" ; break;
				    	case 5 : std::cout<<cashDenominations[i]<< " $2 Bills \n" ; break;
				}
				i++;
			}
		}


		//increment system cash
		void updateMoneyInventory(){
			for(int i=0;i<6;i++){
				systemCash[i] += insertedCash[i];
			}
		}

		public:
			VendingMachine() {
				for (int i = 0; i < 6; ++i) {
					quantity[i] = 0;
					systemCash[i] = 0;
					insertedCash[i] = 0;
				}
			}

			// power house of the vending machine class
			void operate(){
				std::cout<<"Transaction has been executed \n";
				display();
				float totalCost = calculateTotalPrice();	
				bool status = confirmOrder(totalCost);

				float totalCashReceived = 0.0;
				int refund[6];
				if(status){
					totalCashReceived =  getMoneyFromConsumer();
					if(totalCashReceived >= totalCost){
						vendItems();
						updateMoneyInventory();
						if(totalCashReceived > totalCost){
							std::cout<<"\nPlease find a refund of $ "<<totalCashReceived-totalCost<<" along with your purchase\n";
							returnCash(totalCashReceived-totalCost);
						}	
					}
					else {
						std::cout<<"\nTranscation failed. Cash received was $"<< totalCost-totalCashReceived <<" dollars less than cost of items.\n";
					}
				}

				// cleaning up from previous transaction
				for(int i=0;i<6;i++){
					insertedCash[i]=0;
					itemsToBuy[i]=0;
				}	
			}

			// Function for retailer to update quantity
			void setInventory(int newQuantities[6]) {
				for (int i = 0; i < 6; ++i) {
					quantity[i] += newQuantities[i];
				}
			}

			void setMoney(int newMoneyCount[6]) {
				for (int i = 0; i < 6; ++i) {
					systemCash[i] += newMoneyCount[i];
				}
			}
		};


int main(){
	// Requests retailer to enter a password to establish fucnctionalities
	int password;
	int counter=1;
	VendingMachine *vendingMachine = new VendingMachine();
	std::cout<<"Welcome to vendZone!\n";


	// Initializing the quantities of all the items in the Vending Machine in the specific order
	int quantities[6] = {10, 10, 10, 10, 10, 10};

	// Initializing the number of coins in the specific order of penny, nickel, dime, quart, $1, $2
	int denominations[6] = {20, 20, 20, 20, 20, 20};

	// Presents a menu to the retailor with options to set inventory, reset system or begin the Vending Machine
	while(1) {
		std::cout<<"Please enter your passcode to perform \n 1. update items and money \n 2. reset system \n 3. begin the business. \n \n";
		std::cin>>password;
		switch(password){
	    	case 1: 
	    		std::cout<<"Updating Items... Items Updated.\n";
	    		

	    		vendingMachine->setInventory(quantities);
	  			vendingMachine->setMoney(denominations);
	  			break;
	  		case 2:
	  			int d,q;
	  			std::cout<<"Please enter quantities for the items";
	  			for(int i=0;i<6;i++){
	  				std::cin>>q;
	  				quantities[i]=q;
	  			}
	  			std::cout<<"Please enter count of coins for each denomination";
	  			for(int i=0;i<6;i++){
	  				std::cin>>d;
	  				denominations[i]=d;
	  			}
	  			vendingMachine->setInventory(quantities);
	  			vendingMachine->setMoney(denominations);
	  			break;
	      	case 3: 
	     		while(1){
	    			vendingMachine->operate();
		   		} 
		   		break;
		   	default: 
		   		while(1){
		   			vendingMachine->operate();
		   		} 
		   		break;
		}
	}
	std::cout<<"Thank you for working with us";
	return 0;
}
