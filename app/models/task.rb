# frozen_string_literal: true

# Task that a user can complete
class Task < ApplicationRecord
  validates :name, length: { maximum: 50, minimum: 5 }
  validates :description, length: { maximum: 250, minimum: 5 }
  validates :points, numericality: true
  # Our form seems to add .0 after even integer numbers
  validates :difficulty, numericality: true # { only_integer: true }

  # Make sure daily tasks that depend on this task are destroyed if this task is destroyed
  has_many :daily_tasks, dependent: :destroy
end
