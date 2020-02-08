# frozen_string_literal: true

# Refreshes the tasks for a single user
class RefreshUsersDailyTasksJob < ApplicationJob
  queue_as :default

  def perform(user_id)
    user = User.find(user_id)
    user.recreate_daily_tasks
    user.save!
  end
end
