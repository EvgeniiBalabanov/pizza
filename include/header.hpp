#pragma once

#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <optional>

enum Specification {
  kGood,
  kBad,
  kNeutral
};

class Client;

class Group : public std::enable_shared_from_this<Group> {
public:
  Group(Specification specification) : specification_(specification) {};
  void AddRelation(Specification specification);
  size_t GetCountClient() const;
  void GetPizzaIngredients(std::vector<std::string>& ingredients);
  std::pair<bool, std::shared_ptr<Group>> GetOrMakeBufferGroup(Specification specification);
  void ClearBuffer();
private:
  std::shared_ptr<Group> GetBufferGroup(Specification specification);
  void AddRelation(Specification specification, std::shared_ptr<Group> group);
  struct GroupBuffer {
    std::shared_ptr<Group> good;
    std::shared_ptr<Group> bad;
  };
  std::shared_ptr<GroupBuffer> buffer_; // Временное хранение групп для создания связей
  std::shared_ptr<Group> main_parrent_; // Группа в которой текущий ингредиент был Specification::kNeutral
  std::shared_ptr<Group> additional_parrent_; // Группа в которой предыдущий ингредиент был Specification::kNeutral
  Specification specification_; // Окрас этой группы
  // std::vector<std::unique_ptr<Client>> clients_; // Клиенты этой группы
  // std::optional<size_t> count_client_; // Количество (заполняется в конце)
  std::optional<std::string> ingredient_name_;
};

class Client {
public:
  Client(std::shared_ptr<Group> share) : share_(share) {}
  std::shared_ptr<Group> PrepareGroup(Specification specification);
private:
  std::shared_ptr<Group> share_; // Принадлежность к группе
};

class Ingredient {
public:
  explicit Ingredient(const std::string& name) : name_(name) {}
  void AddingGroups();
  void AddClient(std::shared_ptr<Client> client, Specification specification);
private:
  std::vector<std::shared_ptr<Group>> PrepareGroups(Specification specification);
  void AddRelations(std::vector<std::shared_ptr<Group>>& groups, Specification specification);
  void ClearBuffers(std::vector<std::shared_ptr<Group>>& groups);
  std::vector<std::shared_ptr<Client>> good_; // Клиенты которым нужен ингредиент
  std::vector<std::shared_ptr<Client>> bad_; // Клиенты которые против ингредиента
  std::string name_;
};

using Clients = std::unordered_map<std::string, std::shared_ptr<Client>>;
using Ingredients = std::unordered_map<std::string, std::shared_ptr<Ingredient>>;

std::shared_ptr<Group> GetBestGroup(/*groups*/);

void SetIngredient(Ingredients& ingredients, const std::string& name, std::shared_ptr<Client> client, Specification specification);