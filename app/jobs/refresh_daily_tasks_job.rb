# frozen_string_literal: true

# Queues jobs to refresh daily tasks of all users
class RefreshDailyTasksJob < ApplicationJob
  queue_as :default

  after_perform do |_job|
    RefreshDailyTasksJob.set(wait: 1.day).perform_later
  end

  def perform(*_args)
    logger.info 'Refreshing daily tasks for all users'

    User.all.each { |user|
      RefreshUsersDailyTasksJob.perform_later user.id
    }
  end
end
