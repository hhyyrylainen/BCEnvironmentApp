# frozen_string_literal: true

FIRST_TASK_BADGE ||= 'First Task'
ALL_TASK_DONE_BADGE ||= 'All Done'

# Main page controller
class HomeController < ApplicationController
  protect_from_forgery
  before_action :authenticate_user!, only: %i[done undo]

  def index
    time = DateTime.now - 1.day
    @daily_users = User.where(['last_active >= ? OR current_sign_in_at >= ?',
                               time, time]).count

    return unless user_signed_in?

    # Force create daily tasks now if missing completely
    RefreshUsersDailyTasksJob.perform_now current_user.id if current_user.daily_tasks.empty?
    tasks = current_user.daily_tasks.all
    @tasks_left = tasks_left tasks
    @tasks_done = tasks.filter(&:complete)
    @current_level = current_user.level
    @level_progress, @points_left = current_user.level_progress
  end

  def done
    tasks, problem = actionable_tasks

    return if problem

    unless tasks.empty?
      tasks.each { |daily_task|
        logger.info "User (#{current_user.email}) has completed daily task: #{daily_task.id}"

        daily_task.complete = true
        daily_task.save!

        current_user.points = 0 if current_user.points.nil?
        current_user.points += daily_task.task.points
      }

      current_user.mark_action
      grant_badges
      current_user.save!
    end

    redirect_to home_index_path
  end

  def undo
    tasks, problem = actionable_tasks

    return if problem

    unless tasks.empty?
      tasks.each { |daily_task|
        logger.info "User (#{current_user.email}) has undone daily task: #{daily_task.id}"

        daily_task.complete = false
        daily_task.save!

        current_user.points = 0 if current_user.points.nil?
        current_user.points -= daily_task.task.points
      }

      current_user.points = 0 if current_user.points.negative?

      current_user.mark_action
      grant_badges
      current_user.save!
    end

    redirect_to home_index_path
  end

  private

  # Extract keys like 'completed_33: 1' to be '33: 1'
  def task_select_params
    params.require(:home).permit!

    list = params[:home].select { |key, _value| key.match(/completed_\d+/i) }.to_h

    Hash[*list.map { |key, value|
           [key.split('_')[1].to_i, value.to_i]
         } .flatten]
  end

  def actionable_tasks
    result = []
    task_select_params.each { |key, value|
      next if value != 1

      daily_task = DailyTask.find(key)

      if daily_task.user.id != current_user.id
        flash[:alert] = "Can't mark another user's task done"
        redirect_to home_index_path
        return [[], true]
      end

      result.append daily_task
    }

    [result, false]
  end

  def tasks_left(tasks)
    tasks.filter { |i| !i.complete }
  end

  def grant_badges
    tasks = current_user.daily_tasks.all
    left_count = tasks_left(tasks).count

    if current_user.granted_badges.none? { |badge| badge.name == FIRST_TASK_BADGE }
      # Granting badge 'First Task'
      logger.info "Granting first task to user (#{current_user.email})"
      current_user.granted_badges.create! name: FIRST_TASK_BADGE
    end

    if left_count.zero?
      # Granting badge 'All Done'
      logger.info "Granting badge all done to user (#{current_user.email})"
      current_user.granted_badges.create! name: ALL_TASK_DONE_BADGE
    end
  end
end
