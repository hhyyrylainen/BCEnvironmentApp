# frozen_string_literal: true

# Main page controller
class HomeController < ApplicationController
  def index
    time = DateTime.now - 1.day
    @daily_users = User.where(['last_active >= ? OR current_sign_in_at >= ?',
                               time, time]).count

    if user_signed_in?
      @current_level = current_user.level
      @level_progress, @points_left = current_user.level_progress
    end
  end
end
