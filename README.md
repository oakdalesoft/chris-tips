*** Lesson 1: Classes ***

lesson1.x = 10 lesson1.y = 20 lesson1.z = 30

lesson1_1.x = 100 lesson1_1.y = 0 lesson1_1.z = 1

lesson1_2.x = 0 lesson1_2.y = 0 lesson1_2.z = 1

lesson1_3 : calling KludgeUtils::add(1,2) = 3 calling FudgeUtils::add(1,2) = 4

lesson1_3 : calling KludgeUtils::complex_function(velocity{1,2,3}, position{10,10,10}) = 130

*** Lesson 2: Pointers are dead ***

lesson2 : num = 1234 and refnum = 1234

lesson2 : now after increment num = 1235 and refnum = 1235

lesson2_1 : this is how you access wrapped safe, like a pointer (*safe).x 100

lesson2_1 : can also access wrapped quick_safe, by function (quick_safe.get())->x 400

lesson2_2 : using a loop safely with a collection ...

looking at values x, y, z with 1 2 3

looking at values x, y, z with 4 5 6

looking at values x, y, z with 7 8 9

