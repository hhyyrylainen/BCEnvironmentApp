# frozen_string_literal: true

# Main page controller
class HomeController < ApplicationController
  protect_from_forgery
  before_action :authenticate_user!, only: %i[done undo]

  def index
    time = DateTime.now - 1.day
    @daily_users = User.where(['last_active >= ? OR current_sign_in_at >= ?',
                               time, time]).count

    if user_signed_in?
      # Force create daily tasks now if missing completely
      RefreshUsersDailyTasksJob.perform_now current_user.id if current_user.daily_tasks.empty?
      tasks = current_user.daily_tasks.all
      @tasks_left = tasks.filter { |i| !i.complete }
      @tasks_done = tasks.filter(&:complete)
      @current_level = current_user.level
      @level_progress, @points_left = current_user.level_progress
    end
  end

  def done
    logger.info("params: #{params}")
    redirect_to home_index_path
  end

  def undo
    logger.info("params: #{params}")
    redirect_to home_index_path
  end
end
