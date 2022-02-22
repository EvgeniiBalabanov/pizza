#include "header.hpp"
#include <iostream>

int main(void) {
  Clients clients;
  Ingredients ingredients;
  auto base_group = std::make_shared<Group>(Specification::kNeutral);

  // init clients and ingredients
  auto cl1 = std::make_shared<Client>(base_group);
  clients.emplace("one", cl1);
  ingredients["cheese"].AddGood(cl1);
  ingredients["pepper"].AddGood(cl1);

  auto cl2 = std::make_shared<Client>(base_group);
  clients.emplace("two", cl2);
  ingredients["basil"].AddGood(cl2);
  ingredients["pineapple"].AddBad(cl2);

  auto cl3 = std::make_shared<Client>(base_group);
  clients.emplace("third", cl3);
  ingredients["basil"].AddBad(cl3);
  ingredients["tomatoes"].AddGood(cl3);
  ingredients["mushrooms"].AddGood(cl3);

  // Splitting Tree
  for (auto& iter : ingredients) {
    auto& ingredient = iter.second;
    ingredient.AddingGroups();
  }

  return 0;
}