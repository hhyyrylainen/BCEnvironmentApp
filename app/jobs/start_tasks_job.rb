# frozen_string_literal: true

class StartTasksJob < ApplicationJob
  queue_as :default

  def perform(*_args)
    logger.info 'Checking if all background jobs are queued...'

    set = Sidekiq::ScheduledSet.new

    check_refresh_daily set
    check_remind set

    logger.info 'Done checking'
  end

  def check_refresh_daily(set)
    if set.any? { |job|
         job.display_class == 'RefreshDailyTasksJob'
       }
      return
    end

    RefreshDailyTasksJob.set(wait: 15.seconds).perform_later
    logger.info 'Refresh daily task queued'
  end

  def check_remind(set)
    if set.any? { |job|
         job.display_class == 'RemindUsersToLoginJob'
       }
      return
    end

    RemindUsersToLoginJob.perform_later
    logger.info 'Remind login task queued'
  end
end
