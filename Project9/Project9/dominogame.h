#pragma once
#include "dominoset.h"
#include "domino.h"
#include "player.h"
#include <iostream>
#include <limits> // For std::numeric_limits
class dominogame
{
public:
	// Constructor - Initializes a new domino game
	// Sets up players, empty board, and starting player
	dominogame()
		: player1(), player2(), boardLeft(0, 0), boardRight(0, 0), currentPlayer(1) {
		// ...
	}
	// Main game initialization and loop
	// Handles dealing tiles, first move, and game progression

	void startgame() {
		// Initialize players
		dominoset set;
		set.shuffle();
		// Deal tiles to players
		for (int i = 0; i < 7; i++) {
			player1.addTile(set.draw());
			player2.addTile(set.draw());

		}
		// First tile on board
		domino firstTile = set.draw();
		boardLeft = firstTile;
		boardRight = firstTile;

		//game loop
		currentPlayer = 1; // Start with player 1
		while (!gameOver()) {
			playTurn();
			switchPlayer();
		}
		announceWinner();
	}


private:
	  // Game components
    player player1;     // Human or AI player 1
    player player2;     // Human or AI player 2
    domino boardLeft;   // Current left end of the domino chain
    domino boardRight;  // Current right end of the domino chain
    int currentPlayer;  // Tracks whose turn it is (1 or 2)

	bool gameOver() const {
		return player1.hasWon() || player2.hasWon();
	}
	void announceWinner() const {
		if (player1.hasWon()) {
			std::cout << "\nPlayer 1 wins!\n";
		}
		else {
			std::cout << "\nPlayer 2 wins!\n";
		}
	}
	void switchPlayer() {
		currentPlayer = (currentPlayer == 1) ? 2 : 1;
	}

	void displayGameState() const {
		std::cout << "\nCurrent Board: ";
		boardLeft.display();
		std::cout << " - ";
		boardRight.display();
		std::cout << "\n";
	}
	// Helper function to get valid tile selection from player
	// Ensures input is within valid range of player's hand
	int getValidTileChoice(const player& p) const {
		int choice;
		while (true) {
			std::cout << "Choose tile to play (0-" << p.getHandSize() - 1 << "): ";
			if (std::cin >> choice && choice >= 0 && choice < p.getHandSize()) {
				return choice; //valid choice
			}
			// Clear error flags
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please try again.\n";
		}
	}
	void playTurn() {
		player& current = (currentPlayer == 1) ? player1 : player2;

		displayGameState();
		std::cout << "Player " << currentPlayer << "'s tiles: ";
		current.displayHand();

		// Check if player has valid moves
		if (!current.hasValidMove(boardLeft, boardRight)) {
			std::cout << "No valid moves - turn skipped.\n";
			return;
		}


		// Keep trying until a valid move is made
		while (true) {
			int tileChoice = getValidTileChoice(current);
			domino selectedTile = current.getTile(tileChoice);

			if (current.playtile(selectedTile, boardLeft, boardRight)) {
				std::cout << "Played: ";
				selectedTile.display();
				std::cout << std::endl;
				break;
			}
			else {
				std::cout << "Invalid move! That tile doesn't match either end of the board.\n";
			}
		}
	}

		
};

