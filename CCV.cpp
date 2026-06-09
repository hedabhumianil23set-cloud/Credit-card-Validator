#include <iostream>
#include <string>
#include <regex>

bool isValidCreditCard(const std::string& cardNumber) {
    // Remove any spaces or dashes from the card number
    std::string strippedNumber;
    for (char c : cardNumber) {
        if (isdigit(c)) {
            strippedNumber += c;
        }
    }

    // Check if the card number is empty or contains non-digit characters
    if (strippedNumber.empty() || !std::regex_match(strippedNumber, std::regex("[0-9]+"))) {
        return false;
    }

    // Check card number length (Visa: 13 or 16 digits, Mastercard: 16 digits)
    int len = strippedNumber.length();
    if (len != 13 && len != 16) {
        return false;
    }

    // Validate the card number using the Luhn algorithm
    int sum = 0;
    bool doubleDigit = false;
    for (int i = len - 1; i >= 0; --i) {
        int digit = strippedNumber[i] - '0';
        if (doubleDigit) {
            digit *= 2;
            if (digit > 9) {
                digit = (digit % 10) + 1;
            }
        }
        sum += digit;
        doubleDigit = !doubleDigit;
    }
    return (sum % 10 == 0);
}
std::string getCreditCardType(const std::string& cardNumber) {
    if (cardNumber.length() >= 13 && cardNumber.length() <= 16) {
        if (cardNumber[0] == '4') {
            return "Visa";
        } else if (cardNumber.substr(0, 2) == "51" || cardNumber.substr(0, 2) == "52" || 
                   cardNumber.substr(0, 2) == "53" || cardNumber.substr(0, 2) == "54" ||
                   cardNumber.substr(0, 2) == "55") {
            return "Mastercard";
        }
    }
    return "Unknown";
}

int main() {
    std::string cardNumber;
    std::cout << "Enter credit card number: ";
    std::cin >> cardNumber;

    if (isValidCreditCard(cardNumber)) {
        std::string cardType = getCreditCardType(cardNumber);
        if (cardType != "Unknown") {
            std::cout << "Valid " << cardType << " credit card." << std::endl;
        } else {
            std::cout << "Valid credit card, but unknown type." << std::endl;
        }
    } else {
        std::cout << "Invalid credit card number." << std::endl;
    }

    return 0;
}