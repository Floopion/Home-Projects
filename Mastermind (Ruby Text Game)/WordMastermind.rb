=begin
  The Game Class is Respoinsible for the running
  and managment of the game, holds the game state
  and tells the screen class which screen to display.
  It can set up new games, Importing words from a text file,
  It can also validate the appropriatness of these words, or
  of player input, and reject them if they dont meet requirments.

=end
class Game

  #Game Constants
  WORDSIZE = 4
  ERRORMESSAGE = 'Invalid Input! Please enter a valid '

  # Game Constructor
  def initialize
    @word_list = IO.readlines('02-word-list.txt')
    @whole_word
    @word_to_guess = []
    @feedback = Array.new(5, ' |X| ')
    @player = Player.new
    @screens = Screen.new
    @turn_number = 1
  end

  # set up the wordlist for a new game.
  def setup
    to_delete = []
    @word_list.each do |word|

      # Run the word through the validator and return if it is valid or not
      status = validate_word(word)

      # If the words invalid add it to the list of words to delete.
      to_delete.push(word) if status
    end

    # Remove all the invalid words
    to_delete.each do |invalid_word|
      @word_list.delete(invalid_word)
    end

    # Generate a random number in range of the world list length, the word at this
    # index is the game word, split that into an array of chars, using strip incase there is random
    # whitespace for whatever reason
    word_index = rand(@word_list.length)
    @whole_word = @word_list[word_index]
    @word_to_guess = @word_list[word_index].strip.split('')

    home
  end

  # This Method holds all of the home menu / title screen controls From here the player can choose to quit the game
  # or start a new one.
  def home

    # Tell Screen Manager to Display the home screen
    @screens.main

    # Forever while loop to stay in the menu until valid input is received.
    # Convert input to uppercase and sanitize whitespace.
    # Each switch case exits to its respective methods.
    # Close the Window if player wants to Quit.
    # If they want to start the game, tell screen manager to change screen passing it, the current turn number,
    # turn, "un-chopped" player guess, the list of player characters and a feedback list so that the screen
    # class can easily display these where it needs to.
    # and run the game method.
    while true
      # Recieve player input sanitising any whitespace
      option = gets.upcase.strip
      case option
      when 'Q'
        close
      when 'G'
        # Change the screen to the turn limit screen
        @screens.turn_limit

        # Get the max ammount of turns the player wants to play
        # A do..While loop has been used to validate correct input has been entered
        loop do
          #get player input and automatically set it to lowercase, to avoid issues comparing ths stings later on
          tries = gets.to_i
          if tries > 0 && tries < 21
            @player.turn_limit = tries
            @screens.running(@turn_number, @player.turn_limit, @player.player_guess, @player.whole_word, @feedback)
            break
          end
          puts ERRORMESSAGE + 'number.'
          print 'Guess Limit: '
        end

        # Run the Game
        game_run
      else
        puts ERRORMESSAGE + 'menu option.'
        print 'Option:'
      end
    end
  end

  # This method holds all of the actual Game Logic it accept a players guess and call to see if both that guess is
  # a valid word for the game, and call to see how that guess compares to the game word. Once it has heard from both
  # these methods it will increment the turn and the ask the player if it has won / check if the players turns exceed
  # the games turns. If either of these are true, it will pass the screen manager, the variables it needs to display
  # the correct game overs screen. If the player hasn't lost, it will pass the screen manager an updated copy of
  # all the game variables, and then run a new turn.
  def game_run
    # Set the Guess to be invalid to stay in the while loop
    invlaid_guess = true

    # Keep Asking for a valid Guess While the current one is invalid
    while invlaid_guess
      # Trim The user input of whitespace and convert it to lowercase
      guess = gets.strip!.downcase

      # Run the word through the validator, if it returns invalid (False) then display an error message to try input again
      # Don`t flip the invalid guess bool unless invalid returns as true (I realise this may read a little confusing with
      # how I`ve chosen to name the bool`)
      unless validate_word(guess)
        invlaid_guess = false
      else
        puts ERRORMESSAGE + 'word.'
        print 'Option:'
      end
    end

    #Assign the players guess so that you can easily display on the next turn
    @player.whole_word = guess

    #Method Checks the players Guess against the game word
    check_answer(guess)

    # increment the turn
    @turn_number += 1

    # Check if the player has won or the turn limit has been exceeded
    if @player.won || @turn_number > @player.turn_limit
      # tell The screen manager to print the game over screen and wether the player has won or lost
      if @player.won
        @screens.game_over("WIN", @turn_number, @whole_word)
        play_again
      else
        @screens.game_over("LOSE", @turn_number, @whole_word)
        play_again
      end
      #If the game has not ended Tell the screen manager to print the game screen again and run the game
    else
      @screens.running(@turn_number, @player.turn_limit, @player.player_guess, @player.whole_word, @feedback)
      # Run the Game
      game_run
    end
  end


  #This method is used to check the user guess against the game answer It not only compares the guess and game arrays
  # but if necessary compares the characters aswell, for this reason the core of the checks is run as a for loop and
  # not a foreach, so that i can keep track of the index numbers of the individual characters.
  def check_answer(player_guess)

    #Split the players guess into an array of chars
    player_chars = player_guess.split('')

    # First see if the player list equals the game list
    # If it does the player has won and there is no point running anymore checks.
    if player_chars == @word_to_guess
      @player.won = true
    #Otherwise.....
    else
      # Roll Through each character in the player guess array
      for char_index in 0..WORDSIZE
        # Check if that character exists in the game word array
        # if it doesnt we dont need to check its position
        if @word_to_guess.include?(player_chars[char_index])
          # Check if the Character exists in the same word position as the game word
          if @word_to_guess[char_index] == player_chars[char_index]
            # If it does, mark the position as correct
            @feedback[char_index] = ' |O| '
          else
            # Otherwise mark it as in the word, but the wrong position
            @feedback[char_index] = ' |-| '
          end
        else
          # if the character is not in the word, mark it as wrong.
          @feedback[char_index] = ' |X| '
        end
        # Add the Players guess, to the guess array for easy printing in the screen class
        @player.player_guess[char_index] = '  '+player_chars[char_index].to_s+'  '
      end
    end
  end

  # This method accepts a word / input and returns if it valid for the game
  def validate_word(word)

    # Remove the spaces from the ends of the words and chop it into characters
    chars = word.chomp.split('')
    invalid = false

    # Check if the word or input is 5 characters, Reject it if its not
    if chars.length != 5
      invalid = true
    end

    # See if the character appears in the word more than once, otherwise use regex`s to test for numbers and characters
    # The first regex uses the shorthand \W which looks for anything that is NOT [0-9a-zA-Z_] as a quick way to wittle
    # out characters such as !@. The second looks for anything that IS a number. the match method is used to check if
    # your character matches any of the regex conditions.
    # It is worth noting these checks will always be run UNLESS invalid has already been flipped to true.
    # If any of these evaluate, flip invalid to true
    chars.each do |char|
      unless invalid
        invalid = true if word.count(char) > 1 || char.match(/\W/) || char.match(/[0-9]/)
      end
    end

    #return wether the word is valid or not the word is valid
    return invalid

  end

  # This Method caotrols weather to close the game or start another game for the player
  def play_again
    #forever loop to stay in the menu
    while true
      option = gets.upcase.strip
      case option
        #If the player wants to leave, go to the close method
      when 'Q'
        close
        #if the player wants to play again, clear the screen and  reset the game state
      when 'P'
        system('cls')
        reset
      else
        puts ERRORMESSAGE + 'game option.'
        print 'Option:'
      end
    end
  end

  # Re-run the class constructor again to re-initialize everything as empty / reset game bools
  # Re-run the game setup to get a new word
  def reset
    initialize
    setup
  end

  # close the window with a nice message
  def close
    abort('Thanks for playing!')
  end

end

=begin
  Screen class to control all the nonsensical decorative console banners, this saves me dirtying my code
  with Print and Puts calls everywhere. The Screen class will on most occasions, clear the current output
  off the screen before writing the new one. It will also accept any dynamic variables such as round counters
  and display them where appropriate.
=end
class Screen

  # Display the Turn Screen
  def turn_limit
    system('cls')
    puts '***************************************************************'
    puts '* How many Tries would you like to guess the word? (LIMIT 20) *'
    puts '***************************************************************'
    print 'Guess Limit: '
  end

  # Display the welcome menu
  def main
    system('cls')
    puts '***************************************************************'
    puts '*                  Welcome to Word Mastermind                 *'
    puts '***************************************************************'
    puts ''
    puts '                    Welcome to Mastermind!'
    puts ''
    puts 'The game will randomly choose a five letter word, its your job'
    puts 'to guess the word'
    puts ''
    puts 'Each word will only have 1 occurance of any given letter and'
    puts 'after each round the game will let you know if the letters in'
    puts 'your guess are:'
    puts '- In the game word and in the right place'
    puts '- In the game word but in the wrong place'
    puts '- Not in the Game word'
    puts ''
    puts ''
    puts 'Good Luck!'
    puts ''
    puts ' Press G to start the game!'
    puts ' Press Q to quit!'
    puts ''
    print 'Option:'
  end

  # This Screen Accepts the Game turns left and what turn you are on
  # It also accepts and displays both feedback lists so that the player
  # Knows what their last guess was, how the letters corresponded to the game word
  def running(turn, time_to_guess, last_guess, last_word, last_feedback)
    system('cls')
    puts '***************************************************************'
    puts '*                      Word Mastermind                        *'
    puts '***************************************************************'
    puts '* Turn Number: ' + turn.to_s + '                           Turns To Guess: '+time_to_guess.to_s+' *'
    puts '***************************************************************'
    puts ''
    puts '   REMEMBER: Your Word can only have 5 letters, and can only'
    puts '              contain one of each character!'
    puts ''
    puts '|X| = Not in word       |O| = In the word and the correct place'
    puts '|-| = In the word but in the incorrect place '
    puts ''
    puts '             Your Last Guess Was: ' + last_word
    puts ''
    puts '     ' + "#{last_guess}"
    puts '     ' + "#{last_feedback}"
    puts ''
    puts ''
    puts 'What will you guess this turn?'
    puts ''
    print 'Guess: '
  end

  # Game Over Method receives whether the player won or lost, what turn it was, and the game word
  # It then uses these to display the correct screen
  def game_over(result, turns, game_word)
    system('cls')
    if result == 'WIN'
      puts '***************************************************************'
      puts '*                         YOU WON!!                           *'
      puts '***************************************************************'
      puts ''
      puts '                   The word was: ' + game_word
      puts ''
      puts '                You guessed it in ' + turns.to_s + ' turns!'
      puts ''
      puts ''
      puts 'Press "R" to Play Again or "Q" to Quit!'
      puts ''
      print 'Option:'
    else
      puts '***************************************************************'
      puts '*                        YOU LOSE!!                           *'
      puts '***************************************************************'
      puts ''
      puts '                   The word was: ' + game_word
      puts ''
      puts ''
      puts 'Press "P" to Play Again or "Q" to Quit!'
      puts ''
      print 'Option:'
    end
  end
end


=begin
Player class holds, Two lists one for easy feedback display in the
screen class and one with the actual character values to compare against the gae word.
It holds what turn the player is currently on and how many max turns the player would
like to play, and if the player has won the game.

It also holds accessor methods so that it can get and set the vaues from my instance variables.
This was set with instance variables and gets and sets as there are no "public" vars in Ruby and Globals are
generally bad practice.
=end
class Player

  # Player Constructor
  def initialize
    @whole_word = "First Turn!"
    @player_guess = Array.new(5, '  -  ')
    @won = false
    @turn_limit = 0
  end

  # Magic Getter/Setter methods for my instance variables
  attr_accessor :player_guess
  attr_accessor :won
  attr_accessor :turn_limit
  attr_accessor :whole_word

end

# create a new instance of a game and run set up.
# As ruby has no "Main" method, this is how I get things rolling.
new_game = Game.new
new_game.setup
