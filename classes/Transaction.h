// Authors: Bridget Goodwine & Hanjing Zhu
// Emails: bgoodwin@nd.edu & hzhu7@nd.edu
//
// transaction class for the data structures final project on blockchain

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include<iostream>
#include<cstdlib>
#include<string>
#include<iomanip>
#include<vector>
// include SHA-256 here as well?

class Transaction{

private:
  std::string receiver;
  std::string sender;
  std::string amount;
  std::string date;


public:
  // default constructor
  Transaction() : receiver(" "), sender(" "), amount("$0.00"), date("-1/-1/-1") {}

  // overloaded constructor
  Transaction( std::string r, std::string s, std::string a, std::string d ) : receiver(r), sender(s), amount(a), date(d) {}

  // copy constructor
  Transaction( const Transaction& copy ) : receiver(copy.receiver), sender(copy.sender), amount(copy.amount), date(copy.date) {}

  // function that returns the information as a string
  std::string getString (){
      std::string result;
      result.append(this->receiver);
      result += ' ';
      result.append(this->sender);
      result += ' ';
      result.append(this->amount);
      result += ' ';
      result.append(this->date);
      return result;
  }

  // friend opperator
  friend std::ostream& operator<<( std::ostream& output, const Transaction& t ) {
    output << "Receiver: " << t.receiver << std::endl;
    output << "Sender: " << t.sender << std::endl;
    output << "Amount: " << t.amount << std::endl;
    output << "Date: " << t.date << std::endl;

    return output;
  }

};

#endif
