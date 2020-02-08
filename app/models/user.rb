# frozen_string_literal: true

# TODO: having a points curve would probably be better
POINTS_PER_LEVEL ||= 100.0

# Main user model
class User < ApplicationRecord
  NULL_ATTRS = %w[username].freeze

  # Include default devise modules. Others available are:
  # , :lockable, :timeoutable,  and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :validatable, :trackable, :confirmable

  validates :email, presence: true, uniqueness: true, length: { maximum: 255 }

  validates :username, length: { maximum: 100, minimum: 5 }, allow_nil: true

  has_many :granted_badges, dependent: :destroy
  has_many :daily_tasks, dependent: :destroy

  before_validation :nil_if_blank

  def admin?
    admin == true
  end

  def level
    if !points
      0
    else
      (points / POINTS_PER_LEVEL).floor.to_i
    end
  end

  def level_progress
    if !points
      [0, POINTS_PER_LEVEL]
    else

      points_over_last_level = points - level * POINTS_PER_LEVEL

      [points_over_last_level / POINTS_PER_LEVEL, POINTS_PER_LEVEL - points_over_last_level]
    end
  end

  def mark_action
    # NOTE: I accidentally also added a column named last_action
    self.last_active = Time.now
  end

  def send_devise_notification(notification, *args)
    devise_mailer.send(notification, self, *args).deliver_later
  end

  def daily_task_count
    5
  end

  def recreate_daily_tasks
    logger.info "Creating daily tasks for user: #{email}"
    # Destroy old
    daily_tasks.destroy_all

    Task.order('RANDOM()').limit(daily_task_count).each { |task|
      daily_tasks.create task: task, complete: false
    }
  end

  protected

  def nil_if_blank
    NULL_ATTRS.each { |attr| self[attr] = nil if self[attr].blank? }
  end
end
