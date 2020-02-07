# frozen_string_literal: true

# Controller for task related actions
class TasksController < ApplicationController
  before_action :authenticate_user!, :require_admin
  def index
    @tasks = Task.order(:id).page params[:page]
  end

  before_action :authenticate_user!, :require_admin
  def new
    @task = Task.new
    @task.points = 10
    @task.difficulty = 1
  end

  before_action :authenticate_user!, :require_admin
  def edit
    @task = Task.find(params[:id])
  end

  before_action :authenticate_user!, :require_admin
  def show
    @task = Task.find(params[:id])
  end

  protect_from_forgery
  before_action :authenticate_user!, :require_admin
  def create
    @task = Task.new(task_params)

    if @task.save
      clear_error
      redirect_to @task
    else
      set_errors
      render 'new'
    end
  end

  protect_from_forgery
  before_action :authenticate_user!, :require_admin
  def update
    @task = Task.find(params[:id])

    if @task.update(task_params)
      clear_error
      redirect_to @task
    else
      set_errors
      render 'edit'
    end
  end

  protect_from_forgery
  before_action :authenticate_user!, :require_admin
  def destroy
    @task = Task.find(params[:id])
    @task.destroy

    redirect_to tasks_path
  end

  private

  def task_params
    params.require(:task).permit(:name, :description, :points, :difficulty)
  end

  def set_errors
    errors = @task.errors.full_messages.join '. '
    flash[:alert] = "Could not save due to errors: #{errors}"
  end

  def clear_error
    flash.delete(:alert)
  end
end
