# frozen_string_literal: true

# TODO: having a points curve would probably be better
POINTS_PER_LEVEL = 100

# Main user model
class User < ApplicationRecord
  NULL_ATTRS = %w[username].freeze

  # Include default devise modules. Others available are:
  # , :lockable, :timeoutable,  and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :validatable, :trackable, :confirmable

  validates :email, presence: true, uniqueness: true, length: { maximum: 255 }

  validates :username, length: { maximum: 100, minimum: 5 }, allow_nil: true

  has_many :granted_badges

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

  def mark_action
    # NOTE: I accidentally also added a column named last_action
    self.last_active = DateTime.now
  end

  def send_devise_notification(notification, *args)
    devise_mailer.send(notification, self, *args).deliver_later
  end

  protected

  def nil_if_blank
    NULL_ATTRS.each { |attr| self[attr] = nil if self[attr].blank? }
  end
end
