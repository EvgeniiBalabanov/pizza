#include "header.hpp"
#include <iostream>

int main(void) {
  Clients clients;
  Ingredients ingredients;
  auto base_group = std::make_shared<Group>(Specification::kNeutral);

  // init clients and ingredients
  auto cl1 = std::make_shared<Client>(base_group);
  clients.emplace("one", cl1);
  SetIngredient(ingredients, "cheese", cl1, Specification::kGood);
  SetIngredient(ingredients, "pepper", cl1, Specification::kGood);

  auto cl2 = std::make_shared<Client>(base_group);
  clients.emplace("two", cl2);
  SetIngredient(ingredients, "basil", cl2, Specification::kGood);
  SetIngredient(ingredients, "pineapple", cl2, Specification::kBad);

  auto cl3 = std::make_shared<Client>(base_group);
  clients.emplace("third", cl3);
  SetIngredient(ingredients, "basil", cl3, Specification::kGood);
  SetIngredient(ingredients, "tomatoes", cl3, Specification::kGood);
  SetIngredient(ingredients, "mushrooms", cl3, Specification::kGood);

  // Splitting Tree
  for (auto& iter : ingredients) {
    auto& ingredient = iter.second;
    ingredient->AddingGroups();
  }

  return 0;
}