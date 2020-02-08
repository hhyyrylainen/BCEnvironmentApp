# frozen_string_literal: true

# Controller for task related actions
class TasksController < ApplicationController
  protect_from_forgery
  before_action :authenticate_user!, :require_admin

  def index
    @tasks = Task.order(:id).page params[:page]
  end

  def new
    @task = Task.new
    @task.points = 10
    @task.difficulty = 1
  end

  def edit
    @task = Task.find(params[:id])
  end

  def show
    @task = Task.find(params[:id])
  end

  def create
    @task = Task.new(task_params)

    if @task.save
      clear_error
      redirect_to @task
    else
      flash_errors @task
      render 'new'
    end
  end

  def update
    @task = Task.find(params[:id])

    if @task.update(task_params)
      clear_error
      redirect_to @task
    else
      flash_errors @task
      render 'edit'
    end
  end

  def destroy
    @task = Task.find(params[:id])
    @task.destroy

    redirect_to tasks_path
  end

  private

  def task_params
    params.require(:task).permit(:name, :description, :points, :difficulty)
  end
end
