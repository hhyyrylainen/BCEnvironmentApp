# frozen_string_literal: true

# Users page controller, for admins only
class UsersController < ApplicationController
  before_action :authenticate_user!, :require_admin
  def index
    @users = User.order(:email).page params[:page]
  end
end
