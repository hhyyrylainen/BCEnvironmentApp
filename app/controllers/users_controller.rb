# frozen_string_literal: true

# Users page controller, for admins only
class UsersController < ApplicationController
  protect_from_forgery
  before_action :authenticate_user!
  before_action :require_admin, except: [:update]

  def index
    @users = User.order(:email).page params[:page]
  end

  def show
    @user = User.find(params[:id])
  end

  def destroy
    @user = User.find(params[:id])

    if @user.id == current_user.id
      flash[:alert] = 'You cannot delete your account this way'
      render 'show'
    else
      @user.destroy

      redirect_to users_path
    end
  end

  def update
    @user = User.find(params[:id])

    editing_self = @user.id == current_user.id

    if !editing_self && !current_user&.admin?
      redirect_to root_path, alert: 'You are not allowed to edit another user'
      return
    end

    if @user.update(user_params)
      clear_error

      if editing_self
        redirect_to profile_path
      else
        redirect_to @user
      end
    else
      flash_errors @user
      if editing_self
        redirect_to profile_path, alert: error_message(@user)
      else
        render 'edit'
      end
    end
  end

  private

  def user_params
    if current_user&.admin?
      params.require(:user).permit(:username, :points)
    else
      params.require(:user).permit(:username)
    end
  end
end
