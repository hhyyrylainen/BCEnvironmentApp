# frozen_string_literal: true

class UsersController < ApplicationController
  before_action :authenticate_user!, :require_admin
  def index; end
end
