# frozen_string_literal: true

class User < ApplicationRecord
  # Include default devise modules. Others available are:
  # , :lockable, :timeoutable,  and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :validatable, :trackable, :confirmable

  validates :email, presence: true, uniqueness: true, length: { maximum: 255 }

  validates :username, length: { maximum: 100, minimum: 5 }, allow_nil: true

  def admin?
    admin == true
  end

  def send_devise_notification(notification, *args)
    devise_mailer.send(notification, self, *args).deliver_later
  end
end
