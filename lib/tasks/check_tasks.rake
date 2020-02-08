# frozen_string_literal: true

namespace :bce do
  desc 'Check that all needed inbuilt tasks are queued'
  task check_tasks: :environment do
    Rails.logger.info 'Queueing a job to check that all needed jobs are queued'
    StartTasksJob.perform_later
  end
end
