int main() {
    cout << "Welcome to CC3K!" << endl;
    cout << "Please choose map: 1.randomly generated, 2.test files." << endl;
    int number;
    cin >> number;
    while (number != 1 && number != 2) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> number;
    }
    string filename = "floor.txt";
    if (number == 2) {
    	cout << "Please input file name." << endl;
	cin >> filename;
    }
    cout << "Please choose your character:" << endl;
    cout << "Human (h)" << endl;
    cout << "Dwarf (d)" << endl;
    cout << "Elf (e)" << endl;
    cout << "Orc (o)" << endl;
    char playerSymbol;
    cin >> playerSymbol;
    while (playerSymbol != 'h' && playerSymbol != 'd' && playerSymbol != 'e' && playerSymbol != 'o') {
        cout << "Invalid character. Please try again." << endl;
        cin >> playerSymbol;
    }
    Game game(playerSymbol, filename);
    game.play(number);
}