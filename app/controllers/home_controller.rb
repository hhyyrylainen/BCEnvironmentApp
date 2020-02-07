# frozen_string_literal: true

class HomeController < ApplicationController
  def index
    time = DateTime.now - 1.day
    @daily_users = User.where(['last_active >= ? OR current_sign_in_at >= ?',
                               time, time]).length
  end
end
