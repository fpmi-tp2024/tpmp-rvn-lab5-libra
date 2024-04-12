# Дополнительная спецификация

[Home](../index.md)    
[Функциональные требования](functionalRequirements.md)  
[Спецификация проекта](specification.md)  
[Дополнительная спецификация](dopSpecification.md)   
[Схема базы данных](databaseSchema.md)  
[Презентация проекта](projectPresentation.md)

# Дополнительная спецификация

#### Ограничения:
Невозможно добавить заказ, если масса груза превышает грузоподъемность машины.

#### Требования к безопасности:
Только администраторы должны иметь возможность обновлять и удалять записи из БД, а также выводить информацию по всем водителям и машинам.

Водители должны иметь доступ только к информации о себе и о своей машине. Водители должны иметь возможность изменять только свой логин и пароль.