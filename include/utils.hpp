/*
    Utility functions
    -----------------
*/


/*
    is_valid_number
    ---------------
    Checks whether the given string is a valid integer.
*/

bool is_valid_number(const std::string& num) {
    for (char digit : num)
        if (digit < '0' or digit > '9')
            return false;

    return true;
}


/*
    notify_invalid_input
    --------------------
    Writes to the standard error stream if the input was not a valid integer.
*/

void notify_invalid_input(const std::string& input) {
    std::cerr << "Invalid input! Expected an integer, got \'" << input << "\'.\n";
}
