#include "header.hpp"
#include <iostream>

void Ingredient::AddGood(std::shared_ptr<Client> client) {
  good_.push_back(client);
}

void Ingredient::AddBad(std::shared_ptr<Client> client) {
  bad_.push_back(client);
}

void Ingredient::AddingGroups() {
  for (Specification specification : {Specification::kGood, Specification::kBad}) {
    auto groups = PrepareGroups(specification);
    AddRelations(groups, specification);
    ClearBuffers(groups);
  }
}

std::vector<std::shared_ptr<Group>> Ingredient::PrepareGroups(Specification specification) {
  std::vector<std::shared_ptr<Group>> new_groups;
  auto clients = (specification == Specification::kGood) ? good_ : bad_;
  for (auto client : clients) {
    auto ptr_new_group = client->PrepareGroup(specification);
    if (ptr_new_group) {
      new_groups.push_back(ptr_new_group);
    }
  }
  return new_groups;
}

void Ingredient::AddRelations(std::vector<std::shared_ptr<Group>>& groups, Specification specification) {
  for (auto group : groups) {
    group->AddRelation(specification);
  }
}

void Ingredient::ClearBuffers(std::vector<std::shared_ptr<Group>>& groups) {
  for (auto group : groups) {
    group->ClearBuffer();
  }
}

std::shared_ptr<Group> Client::PrepareGroup(Specification specification) {

  auto [is_new, group] = share_->GetOrMakeBufferGroup(specification);
  return is_new ? group : nullptr;
}

void Group::ClearBuffer() {
  buffer_ = nullptr;
}

std::pair<bool, std::shared_ptr<Group>> Group::GetOrMakeBufferGroup(Specification specification) {
  if (!buffer_) {
    buffer_ = std::make_shared<Group::GroupBuffer>();
  }
  bool is_new = false;
  auto& group = (specification == Specification::kGood) ? buffer_->good : buffer_->bad;
  if (!group) {
    group = std::make_shared<Group>(specification);
    is_new = true;
  }
  return {is_new, group};
}

std::shared_ptr<Group> Group::GetBufferGroup(Specification specification) {
  std::shared_ptr<Group> group = nullptr;
  if (!buffer_) {
    return nullptr;
  }
  if (specification == Specification::kGood) {
    group = buffer_->good;
  } else if (specification == Specification::kBad) {
    group = buffer_->bad;
  }
  return group;
}

void Group::GetPizzaIngredients(std::vector<std::string>& ingredients) {
  if (specification_ == Specification::kGood) {
    ingredients.push_back(ingredient_name_.value());
  }
  if (main_parrent_) {
    main_parrent_->GetPizzaIngredients(ingredients);
  }
}

void Group::AddRelation(Specification specification) {
  std::shared_ptr<Group> group = GetBufferGroup(specification);
  if (!group) {
    throw "buffer group is nullptr";
  }
  if (main_parrent_) {
    main_parrent_->AddRelation(specification, group);
  }
  if (additional_parrent_) {
    additional_parrent_->AddRelation(specification, group);
  }
  group->main_parrent_ = shared_from_this();
}

void Group::AddRelation(Specification specification, 
                 std::shared_ptr<Group> start) {
  auto stop = GetBufferGroup(specification);
  if (stop) {
    start->additional_parrent_ = stop;
  } else {
    if (main_parrent_) {
      main_parrent_->AddRelation(specification, start);
    }
    if (additional_parrent_) {
      additional_parrent_->AddRelation(specification, start);
    }
  }
}
