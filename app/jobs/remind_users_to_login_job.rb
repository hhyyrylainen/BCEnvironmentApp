# frozen_string_literal: true

REMIND_USER_LIMIT ||= 1.day
STOP_REMINDERS_AFTER ||= 7.days

# Checks which users need reminding to login and reminds them
class RemindUsersToLoginJob < ApplicationJob
  queue_as :default

  after_perform do |_job|
    RemindUsersToLoginJob.set(wait: 30.minutes).perform_later
  end

  def perform(*_args)
    User.all.each { |user|
      next if user.confirmed_at.nil?

      compare_against = [user.current_sign_in_at, user.last_active,
                         user.last_notified].reject(&:nil?).max

      next if compare_against.nil?

      elapsed = Time.now - compare_against
      next unless elapsed > REMIND_USER_LIMIT

      # Skip if it has been more than a week
      next if elapsed > STOP_REMINDERS_AFTER

      logger.info "Reminding #{user.email} to login, elapsed since login: #{elapsed}"
      user.last_notified = Time.now
      user.save!
      RemindersMailer.remind_login(user.id).deliver_later
    }
  end
end
