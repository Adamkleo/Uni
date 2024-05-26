/** SUMMARY AND STEPS:
 * This program is a music competition done through the console.
 * 
 *  1 - Upon running, the main method will be initiated at first.
 *  
 *  2 - Inside the main method is a start method.
 *  
 *  3 - This method will give the user the option to either log in or sign up.
 *  
 *  	Log in:
 *  	- Upon logging in, the mechanism in place will check if the username exists.
 *  	- If it does, the user will have to input a password which is then checked to see if it matches.
 *  	- If the username does not exist, the user will be asked to log in or sign up.
 *  
 *  	Sign up:
 *  	- If the user decides to sign up. The create account method will be called.
 *  	- After going through the steps to create an account. A boolean will return wether the account was successfully created or not.
 *  	- If the boolean returns true, the user can now log in using that created account.
 *  	- if the boolean returns false, that means the user did not create account due to one of many possible factors.
 *  
 *  4 - Upon logging in, the role of the user will be stored inside a variable. That variable is then checked. 
 *   
 *    	- If the variable is fan, the program will provide the options that a fan can access.
 *    	- If the variable is organizer, the program will provide the options that an organizer can access.
 *    	- If the variable is singer, the program will provide the options that a singer can access.	
 *    
 *  5 - Depending on their role, the user can access different options.
 *  
 *  
 *  
 * PER METHOD DETAILS BELOW **/

package GroupProject;

import java.util.Scanner;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Random;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.lang.Integer;

public class MainHash {

	public static HashMap<String, HashMap<String, String>> parentMap = new HashMap();
	/*
	 * HashMap of HashMaps of string against string. The outer HashMap is the
	 * parentMap where all the accounts are located. All HashMaps inside the parent
	 * Map are individual accounts that contain information.
	 */

	public static String loginRoleCheck;
	/*
	 * The user that is currently signed in will have their role stored in this
	 * string for future use
	 */

	public static void main(String[] args) {

		addExistingUsers();
		/* Initializes a set of pre-made accounts for testing purposes. */

		start();
		/*
		 * Starts the program where the user can log in or sign up (More explained in
		 * the method itself).
		 */

	}

	public static String chooseRole() { /* Obtains the role of a user when they decide to create an account. */

		Scanner roleScanner = new Scanner(System.in);

		String fan = "fan";
		String singer = "singer";
		String organizer = "organizer";

		System.out.println("Choose your role: Singer, organizer, or fan? ");
		String roleInput = roleScanner.nextLine();

		if (roleInput.equalsIgnoreCase(singer) || roleInput.equalsIgnoreCase(fan)
				|| roleInput.equalsIgnoreCase(organizer)) {
			// The user inputs a role. If it matches one of the three available roles, The
			// user can continue

			if (roleInput.equalsIgnoreCase(organizer)) {
				// The program takes into account whether the role is an organizer or singer/fan
				// to avoid grammatical mistakes when printing the role.

				System.out.println("You chose to be an " + roleInput + ".");
			} else {
				System.out.println("You chose to be a " + roleInput + ".");
			}
			return roleInput.toLowerCase();
			// The role is return, in lower-case, to be later stored when the account is
			// fully created.

		}

		else {
			// If the role the user chose does not exist, the method will call itself and
			// repeat until the user gets it right.

			System.err.println("You chose a non-existing role.");
			return chooseRole();
		}
	}

	public static HashMap<String, String> createAccount() { // The account is fully created using a combination of various methods that obtain information from the user

		HashMap<String, String> accountMap = new HashMap();
		/*
		 * An account of type HashMap<String, String> is created to be later stored in
		 * the system. At this moment, it is empty.
		 */

		String userRole = chooseRole();
		/*
		 * The role method is closed in order to obtain the user role and its return
		 * value is stored in a string to be inserted into the HashMap later.
		 */

		Scanner myScanner = new Scanner(System.in);
		System.out.print("Choose a username: ");
		/* The user is asked to choose their username. */

		String username = myScanner.next();
		/* The uesrname is stored inside a string. */

		Boolean usernameExists = false;
		/* A boolean is initialized with the value false. */

		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			String usernameEntry = entry.getValue().get("username");
			if (username.equalsIgnoreCase(usernameEntry)) {
				usernameExists = true;
			}
		}
		/*
		 * Using an entryset for loop, every single value in the parent HashMap that is
		 * under the key = "username" is onbtained. Then checks if the username the user
		 * chose matches the username in the current index we are at inside of the
		 * parent HashMap. If it finds the same username in the parent Map, it assigns
		 * the value true to the previous boolean.
		 */
		if (usernameExists == true) {
			System.out.println("An account with those credentials already exists.");
			System.out.print("Would you like to repeat? [Y/N]: ");
			String userChoice = myScanner.next();
			if (userChoice.equalsIgnoreCase("Y")) {
				return createAccount();
			} else {
				return null;
			}
			/*
			 * If the value of the boolean is true, that means the username already exists.
			 * The user is asked if they would like to repeat. If they choose to repeat, the
			 * method will be called on itself and the create account process restarts. If
			 * they choose not to repeat, it returns null which is later used to take the
			 * user back to the log in/sign up place.
			 */

		} else {
			/*
			 * If the Boolean remains false, the user will be asked to choose a password.
			 * The password will be stored in a string.
			 */

			System.out.print("Choose a password: ");
			String password = myScanner.next();

			accountMap.put("role", userRole);
			accountMap.put("fullname", getName()); // The getName method will be called and value returned by it will be
													// put into the account.

			accountMap.put("username", username);
			accountMap.put("password", password);
			/*
			 * The role, username, password, and fullname are put inside the initially
			 * created HashMap which acts as an account.
			 */

			/*
			 * The role is then checked to make sure the proper account is created depending
			 * on the role.
			 */
			if (userRole.equalsIgnoreCase("Singer")) {
				accountMap.putAll(createSingerAccount());
			}
			/*
			 * If the role is "singer," the createSingerAccount method will be called in
			 * order to insert singer-only attributes such as song, etc.
			 */

			if (userRole.equalsIgnoreCase("Organizer")) {
				accountMap.putAll(createOrganizerAccount());
			}
			/*
			 * If the role is "organizer," the createOrganizerAccount method will be called
			 * in order to insert organizer-only attributes such as delete account, etc.
			 */

			System.out.println("Your username is: '" + username + "' and your password is: '" + password + "'");
			return accountMap;
			/*
			 * When the account is complete, the account in the form of a HashMap is
			 * returned for later storing.
			 */
		}
	}

	public static String getName() { // This method is called when creating an account.

		Scanner myScanner = new Scanner(System.in);
		System.out.print("Enter your full name: ");
		String fullName = myScanner.nextLine();
		return fullName;
		// The user inputs their name when creating an account.
	}

	public static Boolean checkUsername() {
		/* Checks if the username exists when logging in. */

		Scanner myScanner = new Scanner(System.in);
		System.out.print("Enter your username: ");
		String usernameInput = myScanner.nextLine();
		/* The user inputs their username. */

		String selectedUser = null;
		/* A null string is created. */

		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			String usernameEntry = entry.getValue().get("username");
			if (usernameInput.equalsIgnoreCase(usernameEntry)) {
				selectedUser = usernameInput;
			}
		}
		/*
		 * Loop through the parent map and extract the usernames. Compare the user input
		 * with the extracted username. If they match, that means the username is
		 * somewhere in the parent HashMap. Assign the value of the username choosen to
		 * selected User
		 */

		if (selectedUser == null) {
			System.out.println("Username does not exist.");
			return false;
		} else {
			loginRoleCheck = usernameInput;
			return checkPassword(selectedUser);
		}
		/*
		 * Once outside the for-loop, check if the value of selected user is null. If
		 * its null, that means the username doesnt exist. Return false to be used
		 * later. If its not null, that means the username exists. The username is
		 * stored inside loginRoleCheck to be later used when checking the role for
		 * various purposes. The method checkPassword is called using selectedUser as
		 * the parameter (More on this in the checkpassword method). After completeing
		 * the checkPassword method, the boolean true will be returned if the log in was
		 * successful and false if not.
		 */
	}

	public static String checkRole() { // After logging in, the role of the user is extracted from the parent HashMap by using the username.

		String roleChecker = parentMap.get(loginRoleCheck).get("role");
		return roleChecker;
		/* The role is returned. */
	}

	public static Boolean checkPassword(String selectedUser) { // This method checks if the password associated with username is correct when the user inputs it.

		Scanner myScanner = new Scanner(System.in);
		System.out.print("Enter your password: ");
		String passwordInput = myScanner.nextLine();
		/* The user inputs their password. */

		String correctPassword = parentMap.get(selectedUser).get("password");
		/*
		 * Using the parameter which is the username, the password associated with that
		 * username is extracted and stored to later check if the user input is correct.
		 */

		if (passwordInput.equalsIgnoreCase(correctPassword)) {
			System.out.println("You have successfully logged in.");
			return true;
		} else {
			System.err.println("Invaid password. Please try again.");
			return checkPassword(selectedUser);
		}
		/*
		 * The user input is compared to the correct password. If they are equal, the
		 * user is now logged in. If they are not equal, we use recursion to repeat the
		 * password process.
		 */
	}

	public static void start() { // The start method is "main menu" of this program. It is first called when the program starts.

		Scanner myScanner = new Scanner(System.in);
		System.out.print("Log in or Sign up? ");
		String choice = myScanner.nextLine();

		if (choice.equalsIgnoreCase("Log in")) {
			Boolean successfulLogin = checkUsername();
			if (successfulLogin == false) {
				start();
			} else {
				String roleChecker = checkRole();
				if (roleChecker.equalsIgnoreCase("fan")) {
					fanOptions();
				}
				if (roleChecker.equalsIgnoreCase("singer")) {
					singerOptions();
				}
				if (roleChecker.equalsIgnoreCase("organizer")) {
					organizerOptions();
				}
			}

		} else if (choice.equalsIgnoreCase("Sign up")) {
			HashMap<String, String> account = createAccount();
			if (account == null) {
				start();
			} else {
				storeAccount(account);
				System.out.println("You can now log in.");
				start();
			}

		} else {
			System.err.println("Invalid input.");
			start();
		}

	}
	/*
	 * If the user selects to log in, the program will go through one of 2 different
	 * cases depending on the log in result. If the checkUsername method returns
	 * false, the program will start again, repeating the whole process for the user
	 * to log in or sign up. If the checkUsername method returns true, the checkRole
	 * method is called. Depending on the value returned bu the checkRole method,
	 * the user will be sent to their role menu.
	 * 
	 * If the user seleects to sign up, the create account process will start. If
	 * the returned value of the createAccount method is null, the account wasnt
	 * successfuly created. The user will go through the start process again. If the
	 * returned value isn't null, the account was successfully created. The
	 * storeAccount method is called to store the returned account. (More on the
	 * storing later)
	 * 
	 * If the user inputs something other than "log in" or "sign up," the system
	 * will print an invalid input error and repeat the start method.
	 */

	public static void storeAccount(HashMap<String, String> accountMap) { // This method will store the account.

		parentMap.put(accountMap.get("username"), accountMap);
		/*
		 * Using the HashMap methods, we store an account in the form of hashMap inside
		 * the parent Map. The key of each account is its username.
		 */
	}

	public static HashMap<String, String> createSingerAccount() { // This method adds attributes to an account if its a singer.

		HashMap<String, String> singerMap = new HashMap<String, String>();

		Scanner myScanner = new Scanner(System.in);

		singerMap.put("song", getSong());

		singerMap.put("country", getCountry());

		singerMap.put("duration", getDuration());

		System.out.println("Would you like to add any special arrangments for the performance? [Y/N]");
		String arrangments;
		if (myScanner.nextLine().equalsIgnoreCase("Y")) {
			System.out.println("Input your special arrangments request: ");
			arrangments = myScanner.nextLine();
		} else {
			arrangments = "No special arrangments";
		}
		singerMap.put("arrangments", arrangments);

		String status = "Open";
		singerMap.put("status", status);

		String initialVote = "0";
		singerMap.put("votes", initialVote);

		return singerMap;

		/*
		 * After obtaining values from the singer, the values are inserted in a hashMap.
		 * Upon creating an account, the values inside the hashMap are put inside the
		 * full accountMap.
		 */
	}

	public static String getDuration() { // This method gets the duration of the song.
		
		Scanner myScanner = new Scanner(System.in);
		System.out.print("Enter the duration of your song. (hh:mm:ss): ");
		String duration = myScanner.nextLine();
		/* The user inputs a duration */

		String format = "^([0-1][0-9]|[2][0-3]):([0-5][0-9]):([0-5][0-9])$";
		/* Using regex, a format is defined for the duration */

		Pattern myPattern = Pattern.compile(format);
		Matcher myMatcher = myPattern.matcher(duration);
		/*
		 * The format is then compiled into a pattern which is put into a boolean
		 * matcher
		 */

		Boolean result = myMatcher.matches();
		/*
		 * If the boolean returns false, the input doesnt match the format. If the
		 * boolean returns true, the input matches the format.
		 */

		if (result == false) {
			System.out.print("Invalid Input.");
			return getDuration();
		} else {
			return duration;
		}
	}

	public static String getCountry() { // This method obtains the country from a singer and checks if it has been used.

		Scanner myScanner = new Scanner(System.in);
		System.out.print("What country are you from? ");
		String country = myScanner.nextLine();

		Boolean countryExists = false;

		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			String countryEntry = entry.getValue().get("country");
			if (country.equalsIgnoreCase(countryEntry)) {
				countryExists = true;
			}
		}
		/*
		 * Using a for loop, the country Input is compared to every country in the
		 * parent map to check if it already exists. If it exists, the boolean will be
		 * set to true.
		 */

		if (countryExists == true) {
			System.out.println("This country has already been taken.");
			return getCountry();
		}
		/*
		 * If the boolean is set to true, the country exists, recursion is used to
		 * repeat the process. Else, the country doesn't exist and is returned to be
		 * stored.
		 */

		else {
			return country;
		}
	}

	public static String getSong() { // This method checks if the song exists.

		Scanner myScanner = new Scanner(System.in);
		System.out.print("What is the name of your song? ");
		String song = myScanner.nextLine();

		Boolean songExists = false;

		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			String songEntry = entry.getValue().get("song");
			if (song.equalsIgnoreCase(songEntry)) {
				songExists = true;
			}
		}
		/*
		 * Using a for loop, the song Input is compared to every song in the parent map
		 * to check if it already exists. If it exists, the boolean will be set to true.
		 */

		if (songExists == true) {
			System.out.println("This song name has already been used.");
			return getSong();
		}
		/*
		 * If the boolean is set to true, the song exists, recursion is used to repeat
		 * the process. Else, the song doesn't exist and is returned to be stored.
		 */

		else {
			return song;
		}
	}

	public static HashMap<String, String> createOrganizerAccount() { // This method is used to create an organizer  account.																	

		HashMap<String, String> organizerMap = new HashMap();

		String finalDate = "06/12/2021";
		organizerMap.put("Fianl date", finalDate);

		return organizerMap;
	}

	public static void fanOptions() { // If the user is a fan, this method will be called giving different options to use after logging in.

		Scanner myScanner = new Scanner(System.in);
		System.out.println("What would you like to do next?");
		System.out.println("Option 1: Search for a song, singer, or a country. ");
		System.out.println("Option 2: List all the available details in this competition. ");
		System.out.println("Option 3: Vote for a song. ");
		System.out.println("Input the option number.");

		String userChoice = myScanner.nextLine();

		if (userChoice.equals("1")) {
			infoSearch();
		}
		if (userChoice.equals("2")) {
			listAllDetails();
		}
		if (userChoice.equals("3")) {
			voteForSinger();
		} else {
			fanOptions();
		}
	}

	public static void infoSearch() { // This method will search through every information available on a singer matching the users input.									

		Scanner myScanner = new Scanner(System.in);
		System.out.println("Input a name, song, or country.");
		String userChoice = myScanner.nextLine();

		ArrayList<HashMap<String, String>> hashArray = new ArrayList<HashMap<String, String>>();

		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			HashMap<String, String> accountMap = entry.getValue();
			String countryEntry = accountMap.get("country");
			String songEntry = accountMap.get("song");
			String nameEntry = accountMap.get("fullname");
			String roleEntry = entry.getValue().get("role");
			if ((userChoice.equalsIgnoreCase(countryEntry) || userChoice.equalsIgnoreCase(songEntry)
					|| userChoice.equalsIgnoreCase(nameEntry)) && roleEntry.equalsIgnoreCase("Singer")) {
				hashArray.add(accountMap);

			}
		}

		/*
		 * If the user inputs a name, song, or country and the role associated with one
		 * of those is singer, the information will be stored in a Arraylist of
		 * hashMaps. If an account was found from the user input, that account will now
		 * be located in hashArray. If the size of HashArray is 0, that means nothing
		 * was found, If the size of HashArray is 1, that means one thing was found, it
		 * then prints that account that was found. If the size of HashArray is > 1,
		 * that means multiple accounts were found, for example 2 accounts with the same
		 * real name. Both are printed.
		 */

		if (hashArray.size() == 0) {
			System.err.println("Input does not exist");
			infoSearch();
		}
		if (hashArray.size() == 1) {
			System.out.println("Name: " + hashArray.get(0).get("fullname"));
			System.out.println("Song: " + hashArray.get(0).get("song"));
			System.out.println("Country: " + hashArray.get(0).get("country"));
			System.out.println("Votes: " + hashArray.get(0).get("votes"));
		}
		if (hashArray.size() > 1) {
			System.err.println("Multiple singers were found with the same details.\n");
			for (int i = 0; i < hashArray.size(); i++) {
				System.out.println("Name: " + hashArray.get(i).get("fullname"));
				System.out.println("Song: " + hashArray.get(i).get("song"));
				System.out.println("Country: " + hashArray.get(i).get("country"));
				System.out.println("Votes: " + hashArray.get(i).get("votes"));
				System.out.println("");
			}
		}
	}

	public static void listAllDetails() { // This method lists every single details on all singers in the competition in
											// the order chosen by the user.

		Scanner myScanner = new Scanner(System.in);
		System.out.println("Would you like to list all the songs (1), singers (2), or countries (3)? ");
		String userChoice = myScanner.nextLine();

		ArrayList<HashMap<String, String>> singerArray = new ArrayList<HashMap<String, String>>();

		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			HashMap<String, String> accountMap = entry.getValue();
			String roleEntry = entry.getValue().get("role");
			if (roleEntry.equalsIgnoreCase("Singer")) {
				singerArray.add(accountMap);
			}
		}

		/*
		 * After looping through the parent map all the information on all signers will
		 * be located inside singerArray. Then for loop through that singer array to
		 * print out every single account with its corresponding details. The sort
		 * method is called which asks the user if they would like to sort the singers
		 * by increasing or decreasing votes. Then the loop starts and prints out every
		 * single user starting with the userChoice folllowed by the details. When the
		 * printing is complete, the user returns to their options menu. This method
		 * accounts for the typical errors in user input.
		 */

		if (userChoice.equalsIgnoreCase("1")) {
			sortListedDetails(singerArray);
			for (int i = 0; i < singerArray.size(); i++) {
				System.out.println("Song: " + singerArray.get(i).get("song") + " - Details: "
						+ singerArray.get(i).get("country") + ", " + singerArray.get(i).get("fullname") + ", "
						+ singerArray.get(i).get("votes") + " votes");
				System.out.println("");
			}

			returnToOptions();
			return;

		} else if (userChoice.equalsIgnoreCase("2")) {
			sortListedDetails(singerArray);
			for (int i = 0; i < singerArray.size(); i++) {
				System.out.println("Singer: " + singerArray.get(i).get("fullname") + " - Details: "
						+ singerArray.get(i).get("country") + ", " + singerArray.get(i).get("song") + ", "
						+ singerArray.get(i).get("votes") + " votes");
				System.out.println("");
			}

			returnToOptions();
			return;

		} else if (userChoice.equalsIgnoreCase("3")) {
			sortListedDetails(singerArray);
			for (int i = 0; i < singerArray.size(); i++) {
				System.out.println("Country: " + singerArray.get(i).get("country") + " - Details: "
						+ singerArray.get(i).get("song") + ", " + singerArray.get(i).get("fullname") + ", "
						+ singerArray.get(i).get("votes") + " votes");
				System.out.println("");
			}

			returnToOptions();
			return;
		}

		else {
			System.err.println("Invalid Input!");
			returnToOptions();
			return;
		}
	}

	public static void returnToOptions() { // Since list all details is used by two different roles, this method will
											// redirect the user to its proper options depending on its role

		if (loginRoleCheck.equalsIgnoreCase("fan")) {
			fanOptions();
		}
		if (loginRoleCheck.equalsIgnoreCase("organizer")) {
			organizerOptions();
		}
	}

	public static void sortListedDetails(ArrayList<HashMap<String, String>> singerArray) { // This method asks the user
																							// how they want to sort the
																							// listed details. It is
																							// used in the list all
																							// detail method.

		Scanner myScanner = new Scanner(System.in);
		System.out.println("Would you like to list all users ordered by votes (1) or alphabetically (2)?");
		String userOrderChoice = myScanner.nextLine();

		if (userOrderChoice.equalsIgnoreCase("1")) {
			System.out.println("Would you like to list them by ascending (1) or descending (2) votes.");
			String voteOrderChoice = myScanner.nextLine();

			if (voteOrderChoice.equalsIgnoreCase("1")) {
				selectionSortAsc(singerArray);
			} else if (voteOrderChoice.equalsIgnoreCase("2")) {
				selectionSortDsc(singerArray);
			} else {
				System.err.println("Invalid input!");
				listAllDetails();
				return;
			}
		}
		
		else if (userOrderChoice.equalsIgnoreCase("2")) {
			bubbleSortAlph(singerArray);
		} 
		
		else {
			System.err.println("Invalid input!");
			listAllDetails();
			return;
		}
	}

	public static int vote() { // This method obtains a number of votes from 1 to 12 from a fan
		Scanner myScanner = new Scanner(System.in);
		System.out.println("Input a number of votes between 1 and 12");
		int voteCount = myScanner.nextInt();

		if (voteCount <= 12 && voteCount >= 1) {
			return voteCount;
		} else {
			System.err.println("Invalid Input");
			return vote();
		}
	}

	public static void voteForSinger() { // This method allows fans to vote for a singer.

		Scanner myScanner = new Scanner(System.in);

		System.out.println("What song, singer, or country would you like to vote for?");
		String userChoice = myScanner.nextLine();

		ArrayList<HashMap<String, String>> hashArray = new ArrayList<HashMap<String, String>>();

		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			HashMap<String, String> accountMap = entry.getValue();
			String countryEntry = accountMap.get("country");
			String songEntry = accountMap.get("song");
			String nameEntry = accountMap.get("fullname");
			String usernameEntry = accountMap.get("username");
			if (userChoice.equalsIgnoreCase(songEntry) || userChoice.equalsIgnoreCase(nameEntry)
					|| userChoice.equalsIgnoreCase(countryEntry) || userChoice.equalsIgnoreCase(usernameEntry)) {
				hashArray.add(accountMap);

			}
		}

		/*
		 * If the user inputs a name, song, or country and the role associated with one
		 * of those is singer, the information will be stored in a Arraylist of
		 * hashMaps. If an account was found from the user input, that account will now
		 * be located in hashArray. If the size of HashArray is 0, that means nothing
		 * was found, If the size of HashArray is 1, that means one thing was found, the
		 * user can then vote for a singer. If the size of HashArray is > 1, that means
		 * multiple accounts were found, for example 2 accounts with the same real name.
		 * Both are printed and the username for each one is given to the user. The
		 * program will then ask them to input the username of one of the two duplicate
		 * names.
		 */

		if (hashArray.size() == 0) {
			System.err.println("No singer was found with those details.");
			voteForSinger();
		}

		if (hashArray.size() == 1) {
			String currentVoteCount = hashArray.get(0).get("votes");
			int newVoteCount = vote() + Integer.parseInt(currentVoteCount);
			String newVoteCountStr = String.valueOf(newVoteCount);
			hashArray.get(0).put("votes", newVoteCountStr);
			System.out.println("You have successfully voted. You will now be redirected back to the menu.");
			fanOptions();
		}

		if (hashArray.size() > 1) {
			System.err.println("Multiple users were found with the same details.\n");
			for (int i = 0; i < hashArray.size(); i++) {
				System.out.println("Name: " + hashArray.get(i).get("fullname"));
				System.out.println("Username: " + hashArray.get(i).get("username"));
				System.out.println("\n");
			}

			voteForSinger();
		}
		/*
		 * The voting extracts the vote string from the account hashMap, changes it to
		 * an int using parseInt, adds the new number of votes to it and switches back
		 * to string. Then the new amount is put inside the hashMap.
		 */
	}

	public static void organizerOptions() { // This method gives the organizer its options.

		Scanner myScanner = new Scanner(System.in);
		System.out.println("What would you like to do next?");
		System.out.println("Option 1: Add a new singer. ");
		System.out.println("Option 2: Delete a user. ");
		System.out.println("Option 3: List all the available details in this competition. ");
		System.out.println("Option 4: Close the competition. ");
		System.out.println("Input the option number.");

		String userChoice = myScanner.nextLine();

		if (userChoice.equals("1")) {
			addNewSinger();
		}
		if (userChoice.equals("2")) {
			deleteUser();
		}
		if (userChoice.equals("3")) {
			listAllDetails();
		}
		if (userChoice.equals("4")) {
			closeEvent();
		} else {
			organizerOptions();
		}

	}

	public static void afterAddingSinger() { // This method stores the account that organizer created if the creation
												// was successful.

		HashMap<String, String> account = addNewSinger();
		if (account == null) {
			System.err.println("Failed to create account. Returning to home.");
			organizerOptions();
		} else {
			storeAccount(account);
			System.out.println("Account was successfully created.");
			organizerOptions();

		}
	}

	public static HashMap<String, String> addNewSinger() { // This method allows an organizer to create a singer
															// account.

		HashMap<String, String> accountMap = new HashMap();
		String userRole = "singer";

		Scanner myScanner = new Scanner(System.in);
		System.out.print("Choose a username: ");
		String username = myScanner.next();
		Boolean usernameExists = false;
		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			String usernameEntry = entry.getValue().get("username");
			if (username.equalsIgnoreCase(usernameEntry)) {
				usernameExists = true;
			}
		}
		if (usernameExists == true) {
			System.out.println("An account with those credentials already exists.");
			System.out.print("Would you like to repeat? [Y/N]: ");
			String userChoice = myScanner.next();
			if (userChoice.equalsIgnoreCase("Y")) {
				return addNewSinger();
			} else {
				return null;
			}
		} else {
			System.out.print("Choose a password: ");
			String password = myScanner.next();
			accountMap.put("role", userRole);
			accountMap.put("fullname", getName());
			accountMap.put("username", username);
			accountMap.put("password", password);
			if (userRole.equalsIgnoreCase("Singer")) {
				accountMap.putAll(createSingerAccount());
			}
			System.out.println("Account successfully added to the system.\n");
			return accountMap;
		}
	}

	public static void deleteUser() { // This method allows the organizer to delete accounts.
		Scanner myScanner = new Scanner(System.in);
		System.out.println("Input the username, name, song, or country of the user you would like to delete.");
		String userChoice = myScanner.nextLine();

		ArrayList<HashMap<String, String>> hashArray = new ArrayList<HashMap<String, String>>();

		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			HashMap<String, String> accountMap = entry.getValue();
			String countryEntry = accountMap.get("country");
			String songEntry = accountMap.get("song");
			String nameEntry = accountMap.get("fullname");
			String usernameEntry = accountMap.get("username");
			if (userChoice.equalsIgnoreCase(countryEntry) || userChoice.equalsIgnoreCase(songEntry)
					|| userChoice.equalsIgnoreCase(nameEntry) || userChoice.equalsIgnoreCase(usernameEntry)) {
				hashArray.add(accountMap);
			}
		}

		/*
		 * Using a name, username, song, or country, the organizer can delete an
		 * account. Duplicates are also handled in this method.
		 */
		if (hashArray.size() == 0) {
			System.err.println("User does not exist");
			organizerOptions();
		}

		if (hashArray.size() == 1) {
			String username = hashArray.get(0).get("username");
			System.out.println("What is the reason behind this deletion?");
			String deleteReason = myScanner.nextLine();
			parentMap.remove(username);
		}

		if (hashArray.size() > 1) {
			System.err.println("Multiple users were found with the same details.\n");
			for (int i = 0; i < hashArray.size(); i++) {
				System.out.println("Name: " + hashArray.get(i).get("fullname"));
				System.out.println("Username: " + hashArray.get(i).get("username"));
				System.out.println("\n");
			}

			deleteUser();
		}
	}

	public static void closeEvent() { // This method updates all statuses in the parentMap to closed, thus closing the
										// competition.

		ArrayList<HashMap<String, String>> hashArray = new ArrayList<HashMap<String, String>>();
		for (Entry<String, HashMap<String, String>> entry : parentMap.entrySet()) {
			HashMap<String, String> accountMap = entry.getValue();
			hashArray.add(accountMap);
		}
		for (int i = 0; i < hashArray.size(); i++) {
			hashArray.get(i).put("status", "Closed");
		}
	}

	public static void selectionSortAsc(ArrayList<HashMap<String, String>> accountArray) { // SelectionSort

		for (int i = 0; i < accountArray.size(); i++) {
			int m = i;
			for (int j = i; j < accountArray.size(); j++) {

				String jVoteStr = accountArray.get(j).get("votes");
				int jVoteInt = Integer.parseInt(jVoteStr);

				String mVoteStr = accountArray.get(m).get("votes");
				int mVoteInt = Integer.parseInt(mVoteStr);

				if (jVoteInt < mVoteInt) {
					m = j;
				}
			}
			swap(accountArray, i, m);
		}
	}

	public static void selectionSortDsc(ArrayList<HashMap<String, String>> accountArray) { // SelectionSort

		for (int i = 0; i < accountArray.size(); i++) {
			int m = i;
			for (int j = i; j < accountArray.size(); j++) {

				String jVoteStr = accountArray.get(j).get("votes");
				int jVoteInt = Integer.parseInt(jVoteStr);

				String mVoteStr = accountArray.get(m).get("votes");
				int mVoteInt = Integer.parseInt(mVoteStr);

				if (jVoteInt > mVoteInt) {
					m = j;
				}
			}
			swap(accountArray, i, m);
		}
	}
	
    public static void bubbleSortAlph(ArrayList<HashMap<String , String>> accountArray) {
    	
    	for (int i=0 ; i<accountArray.size()-1 ; i++) {
    		for (int j=0 ; j<accountArray.size()-1-i ; j++) {
    			String jSingerStr = accountArray.get(j).get("fullname");
    			String iSingerStr = accountArray.get(i).get("fullname");
    			String j1SingerStr = accountArray.get(j+1).get("fullname");
    			String one = jSingerStr.substring(0,1);
    			String two = iSingerStr.substring(0,1);
    			String three = j1SingerStr.substring(0,1);
    			if( one.compareTo(three)>0 ) {
    				swap(accountArray , j , j+1);
    			}
    		} 	
    	}
    }
    	
	public static void swap(ArrayList<HashMap<String, String>> accountArray, int i, int j) {
		HashMap<String, String> aux = accountArray.get(i);

		accountArray.set(i, accountArray.get(j));
		accountArray.set(j, aux);
	
	}

	public static void singerOptions() {

		Scanner myScanner = new Scanner(System.in);
		System.out.println("What would you like to do next?");
		System.out.println("Option 1: Change the name of the song. ");
		System.out.println("Option 2: Check the number of votes you recived. ");
		System.out.println("Option 3: Specify if you whant the spacial arrangmants for the show. ");
        System.out.println("Option 4: Check the amount of tickets you have sold.");
        System.out.println("Option 5: Return to front page. ");
		System.out.println("Input the option number.");
		String userChoice = myScanner.nextLine();

		if (userChoice.equals("1")) {
			changeSingerDetails();
		}
		if (userChoice.equals("2")) {
			votesInfo();
		}
		if (userChoice.equals("3")) {
			specialArrangmants();
		} 
		if (userChoice.equals("4")) {
			ticketsSold();
		}
		if (userChoice.equals("5")) {
			start();
		}
		else {
			singerOptions();
		}
	}
	
	public static void ticketsSold() { // This methods generates a random number which represents tickets sold
		Random rand = new Random();
		int randomInt = rand.nextInt(500);
		String randomString = Integer.toString(randomInt);
		
		HashMap<String, String> username = parentMap.get(loginRoleCheck);
		
		username.put("tickets", randomString);
		
		System.out.println("You sold " + randomString + " tickets.");
		
	}

	public static void changeSingerDetails() {  //this method will allow you to change the information of your song 

		Scanner myScanner = new Scanner(System.in);
		System.out.println("What would you like to do next?");
	    System.out.println("Option 1: Input the new name of the song.");
	    System.out.println("Option 2: change the duration of the song.");

		String userChoice = myScanner.nextLine();
		
		/*the progrma will give you two options,
		 * one to change the name of the song and the second one will allow you to change the duration*/
		
		if(userChoice.equals("1")) {

			System.out.println("Input the new name of the song.");
			String newSong= myScanner.nextLine();
			HashMap<String, String> username = parentMap.get(loginRoleCheck);
			
   		//the program will receive the new name and change it directly from the hashMap
			
	   		username.put("song", newSong);
	   		System.out.println("The name of the song has been changed to: "+ newSong);

		}
		
		if(userChoice.equals("2")) {

			String newDuration=getDuration();

			HashMap<String, String> username = parentMap.get(loginRoleCheck);
			//the program will receive the new name and change it directly from the hashMap

			username.put("duration", newDuration);
			System.out.println("The duration of the song has been changed.");

		}
		//here the program will let you return to the singers menu or re-do the method
		else {
			
		}
		
		System.out.println("Would you like to return to singers menu? [Y/N]");
		if (myScanner.nextLine().equalsIgnoreCase("Y")) {
			singerOptions();
       } 
		
		else {
	       	System.out.println("you have the option to re-wright the song");
	       	changeSingerDetails();
		}
	}

    public static void votesInfo() {
    	/*in this method will output the number of votes that the singer has recived
    	 * the program will go to the hashMap to get all the information of the votes
    	 *  and it will show the number of votes that the user has received. */
 
    	 String voteCount = parentMap.get(loginRoleCheck).get("votes");
         System.out.println("The number of votes you got is: " + voteCount + " votes");
 
       //here the program will let you return to the singers menu or re-do the method
         Scanner myScanner = new Scanner(System.in);
         System.out.println("Would you like to return to the singer menu? [Y/N]");
         String arrangments;
         System.out.println("You will now be re-directed back to the main menu.");
         singerOptions();

    }

    public static void specialArrangmants() {
    	//here the program is going to show the arrangements that you input earlier 
    	 String specialArrangments = parentMap.get(loginRoleCheck).get("arrangments");
         System.out.println("Your arrengments are: " + specialArrangments ); 
 
       //here the program will let you return to the singers menu or re-do the method
         Scanner myScanner = new Scanner(System.in);
         System.out.println("Would you like to change them again? [Y/N]");
         String arrangments;
         if (myScanner.nextLine().equalsIgnoreCase("Y")) {
        	 singerOptions();
         } else {
        	 specialArrangmants();
         }
    }

    public static void addExistingUsers() { // This method consists of predefind users.
 
        HashMap<String, String> fan1 = new HashMap();
        fan1.put("role", "fan");
        fan1.put("fullname", "adamkaawach");
        fan1.put("username", "adamfk1");
        fan1.put("password", "password");
        storeAccount(fan1);
 
        HashMap<String, String> singer2 = new HashMap();
        singer2.put("role", "singer");
        singer2.put("fullname", "ahmed H");
        singer2.put("username", "ahmedhoff");
        singer2.put("password", "password");
        singer2.put("song", "M.E");
        singer2.put("country", "France");
        singer2.put("duration", "00:03:11");
        singer2.put("arrangments", "no arrangments");
        singer2.put("status", "open");
        singer2.put("votes", "2");
        storeAccount(singer2);
 
        HashMap<String, String> singer3 = new HashMap();
        singer3.put("role", "singer");
        singer3.put("fullname", "ahmed H");
        singer3.put("username", "juantorres");
        singer3.put("password", "password");
        singer3.put("song", "Euphoria");
        singer3.put("country", "Congo");
        singer3.put("duration", "00:12:31");
        singer3.put("arrangments", "water and back up singers");
        singer3.put("status", "open");
        singer3.put("votes", "5");
        storeAccount(singer3);
 
        HashMap<String, String> singer4 = new HashMap();
        singer4.put("role", "singer");
        singer4.put("fullname", "sherif ghali");
        singer4.put("username", "sherif");
        singer4.put("password", "password");
        singer4.put("song", "what are you looking at?");
        singer4.put("country", "Lebanon");
        singer4.put("duration", "00:08:53");
        singer4.put("arrangments", "Flying drones");
        singer4.put("status", "open");
        singer4.put("votes", "4");
        storeAccount(singer4);
 
        HashMap<String, String> organizer1 = new HashMap();
        organizer1.put("role", "organizer");
        organizer1.put("fullname", "joe");
        organizer1.put("username", "majorblake");
        organizer1.put("password", "password");
        storeAccount(organizer1);
 
        HashMap<String, String> singer5 = new HashMap();
        singer5.put("role", "singer");
        singer5.put("fullname", "Carlos Terrero");
        singer5.put("username", "carlangaras");
        singer5.put("password", "password");
        singer5.put("song", "why me?");
        singer5.put("country", "Spain");
        singer5.put("duration", "00:22:41");
        singer5.put("arrangments", "no arrangments");
        singer5.put("status", "open");
        singer5.put("votes", "8");
        storeAccount(singer5);
 
        HashMap<String, String> singer1 = new HashMap();
        singer1.put("role", "singer");
        singer1.put("fullname", "mastulEskat");
        singer1.put("username", "abcd");
        singer1.put("password", "password");
        singer1.put("song", "water in the bottle");
        singer1.put("country", "Portugal");
        singer1.put("duration", "00:22:01");
        singer1.put("arrangments", "fireworks");
        singer1.put("status", "open");
        singer1.put("votes", "3");
        storeAccount(singer1);
 
    }
}
