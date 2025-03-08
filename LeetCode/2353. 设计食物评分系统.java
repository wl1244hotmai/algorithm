 class FoodRatings {

        static class Food {
            String food;
            String cuisine;
            Integer rating;

            public Food(String food, String cuisine, Integer rating) {
                this.food = food;
                this.cuisine = cuisine;
                this.rating = rating;
            }

            public String getFood() {
                return food;
            }

            public String getCuisine() {
                return cuisine;
            }

            public Integer getRating() {
                return rating;
            }

            public void setFood(String food) {
                this.food = food;
            }

            public void setCuisine(String cuisine) {
                this.cuisine = cuisine;
            }

            public void setRating(Integer rating) {
                this.rating = rating;
            }
        }

        Map<String, PriorityBlockingQueue<Food>> cuisineRatingMap = new HashMap<>();
        Map<String, Food> foodNameMap = new HashMap<>();

        public FoodRatings(String[] foods, String[] cuisines, int[] ratings) {
            int n = foods.length;
            for (int i = 0; i < n; i++) {
                Food food = new Food(foods[i], cuisines[i], ratings[i]);
                foodNameMap.put(foods[i], food);
                cuisineRatingMap.computeIfAbsent(cuisines[i], cuisine -> new PriorityBlockingQueue<Food>(
                        n,
               (o1,o2) -> {
                            if (o1.getRating().equals(o2.getRating())) {
                                return o1.getFood().compareTo(o2.getFood());
                            } else {
                                return o2.getRating().compareTo(o1.getRating());
                            }
                        }
                )).add(food);
            }
        }

        public void changeRating(String food, int newRating) {
            Food food_ = foodNameMap.get(food);
            food_.setRating(newRating);

            cuisineRatingMap.get(food_.getCuisine()).remove(food_);
             food_.setRating(newRating);
            cuisineRatingMap.get(food_.getCuisine()).add(food_);
        }

        public String highestRated(String cuisine) {
            return cuisineRatingMap.get(cuisine).peek().getFood();
        }
    }
/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings obj = new FoodRatings(foods, cuisines, ratings);
 * obj.changeRating(food,newRating);
 * String param_2 = obj.highestRated(cuisine);
 */
